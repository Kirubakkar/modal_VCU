/**
 ******************************************************************************
 * @file           : vcu.c
 * @brief          : VCU application implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "vcu.h"
#include "asi.h"
#include "canMessages.h"
#include "canOpen.h"
#include "canSignal.h"
#include "canTx.h"
#include "cmsis_os.h"
#include "steering.h"
#include <string.h>

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Private variables ---------------------------------------------------------*/
static osThreadId_t telems100msTaskHandle;
static osThreadId_t telems1000msTaskHandle;

/* Extracted signals from CmdDrive (0x220) - written from ISR, read from tasks
 */
static volatile float vcuSteerAngle = 0.0f;
static volatile float vcuAped = 0.0f;
static volatile float vcuPrnd = 0.0f;

/* Drive command state */
#define ASI_CAN_ID_OFFSET_STATE 0x1EE
#define ASI_CAN_ID_OFFSET_DRIVE 0x1F2
#define ASI_MAX_MOTOR_CURRENT 100.0f
#define ASI_MAX_REGEN_CURRENT 100.0f

static float remoteState = 0.0f;
static float speedRegulatorMode = 0.0f;
static float throttleCmdFR = 0.0f;
static float throttleCmdFL = 0.0f;
static float throttleCmdRR = 0.0f;
static float throttleCmdRL = 0.0f;
static float speedCommand = 0.0f;

static const osThreadAttr_t telems100msTask_attributes = {
    .name = "vTaskTelems100ms",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

static const osThreadAttr_t telems1000msTask_attributes = {
    .name = "vTaskTelems1000ms",
    .stack_size = 256 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
static void vTaskTelems100ms(void *argument);
static void vTaskTelems1000ms(void *argument);
static void sendDriveData(void);
static void processDriveCommand(void);
static void sendAsiNodeCmd(uint8_t nodeId, float throttleCmd, float speedCmd);
static void sendAsiCmd(void);

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize VCU - runs steering homing sequence.
 *         Must be called from a FreeRTOS task context (uses osDelay).
 */
void initVCU(void) {
  /* Initialize steering subsystem (homing sequence) */
  if (initSteering() == 0) {

    asiInit();
    initTelems();
  }
}

/**
 * @brief  Process incoming CAN messages for VCU.
 *         Called from ISR context (HAL_CAN_RxFifo0MsgPendingCallback).
 * @param  stdId  Standard CAN ID
 * @param  data   Pointer to data bytes
 * @param  dlc    Data length code
 */
void VCU_ProcessRxMessage(uint32_t stdId, uint8_t *data, uint8_t dlc) {
  (void)dlc;

  if (stdId == CAN_ID_CMD_DRIVE) {
    vcuSteerAngle = canExtract(data, &kxCanSignalSteerAng);
    vcuAped = canExtract(data, &kxCanSignalAped);
    vcuPrnd = canExtract(data, &kxCanSignalPrnd);
  }
}

/**
 * @brief  Initialize telemetry - creates periodic telemetry tasks.
 *         Must be called from a FreeRTOS task context.
 */
void initTelems(void) {
  telems100msTaskHandle =
      osThreadNew(vTaskTelems100ms, NULL, &telems100msTask_attributes);

  telems1000msTaskHandle =
      osThreadNew(vTaskTelems1000ms, NULL, &telems1000msTask_attributes);
}

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Telemetry task - runs every 100ms.
 */
static void vTaskTelems100ms(void *argument) {
  (void)argument;

  for (;;) {
    processDriveCommand();
    sendPosition(vcuSteerAngle);

    osDelay(100);
  }
}

/**
 * @brief  Telemetry task - runs every 1000ms.
 */
static void vTaskTelems1000ms(void *argument) {
  (void)argument;

  for (;;) {
    sendDriveData();

    osDelay(1000);
  }
}

/**
 * @brief  Extract signals from received CmdDrive (0x220) and
 *         transmit them as DriveData (0x240).
 */
static void sendDriveData(void) {
  uint8_t txBuf[8] = {0};

  /* Pack already-extracted signals into TX buffer */
  canPack(txBuf, &kxCanSignalSteerAng, vcuSteerAngle);
  canPack(txBuf, &kxCanSignalAped, vcuAped);
  canPack(txBuf, &kxCanSignalPrnd, vcuPrnd);

  /* Transmit on CAN */
  CAN_TxHeaderTypeDef txHeader;

  txHeader.StdId = CAN_ID_DATA_DRIVE;
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = CAN_DLC_DATA_DRIVE;
  txHeader.TransmitGlobalTime = DISABLE;

  CAN_TransmitRetry(&hcan1, &txHeader, txBuf);
}

/**
 * @brief  Send state and command messages to a single ASI motor node.
 * @param  nodeId      CANopen node ID
 * @param  throttleCmd Throttle command for this node
 * @param  speedCmd    Speed command for this node
 */
static void sendAsiNodeCmd(uint8_t nodeId, float throttleCmd, float speedCmd) {
  CAN_TxHeaderTypeDef txHeader;

  /* --- State message (DLC 4) --- */
  uint8_t stateData[8] = {0};

  canPack(stateData, &kxCanSignalAsiState, remoteState);
  canPack(stateData, &kxCanSignalAsiSpeedMode, speedRegulatorMode);

  txHeader.StdId = nodeId + ASI_CAN_ID_OFFSET_STATE;
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 4;
  txHeader.TransmitGlobalTime = DISABLE;

  CAN_TransmitRetry(&hcan1, &txHeader, stateData);

  /* --- Command message (DLC 8) --- */
  uint8_t cmdData[8] = {0};

  canPack(cmdData, &kxCanSignalAsiMaxMotorCurrent, ASI_MAX_MOTOR_CURRENT);
  canPack(cmdData, &kxCanSignalAsiMaxBrakeCurrent, ASI_MAX_REGEN_CURRENT);
  canPack(cmdData, &kxCanSignalAsiTorqueCommand, throttleCmd);
  canPack(cmdData, &kxCanSignalAsiSpeedCommand, speedCmd);

  txHeader.StdId = nodeId + ASI_CAN_ID_OFFSET_DRIVE;
  txHeader.DLC = 8;

  CAN_TransmitRetry(&hcan1, &txHeader, cmdData);
}

/**
 * @brief  Send ASI commands to all 4 motor nodes.
 */
static void sendAsiCmd(void) {
  sendAsiNodeCmd(ASI_NODE_FR, throttleCmdFR, speedCommand);
  sendAsiNodeCmd(ASI_NODE_FL, throttleCmdFL, speedCommand);
  sendAsiNodeCmd(ASI_NODE_RR, throttleCmdRR, speedCommand);
  sendAsiNodeCmd(ASI_NODE_RL, throttleCmdRL, speedCommand);
}

/**
 * @brief  Process drive command from received 0x220 message.
 *         Determines remote state, speed regulator mode, and per-wheel
 *         throttle commands based on PRND and accelerator pedal.
 */
static void processDriveCommand(void) {
  float fAccelPedal = vcuAped;
  uint8_t ucPrnd = (uint8_t)vcuPrnd;
  float fRightMultiplier = -1.0f;
  float fLeftMultiplier = 1.0f;

  // speedCommand = fAccelPedal;

  switch (ucPrnd) {
  case DRIVE_PRND_PARK:
    fAccelPedal = 0.0f;
    speedCommand = fAccelPedal;
    remoteState = 2.0f;
    speedRegulatorMode = 0.0f;
    break;

  case DRIVE_PRND_REVERSE:
    if (fAccelPedal == 0.0f) {
      remoteState = 2.0f;
      speedRegulatorMode = 0.0f;
      fAccelPedal = 0.0f;
      speedCommand = fAccelPedal;
    } else {
      fAccelPedal = -1.0f * fAccelPedal;
      speedCommand = fAccelPedal;
      remoteState = 2.0f;
      speedRegulatorMode = 1.0f;
    }
    break;

  case DRIVE_PRND_NEUTRAL:
    fAccelPedal = 0.0f;
    speedCommand = fAccelPedal;
    remoteState = 1.0f;
    speedRegulatorMode = 0.0f;
    break;

  case DRIVE_PRND_DRIVE:
    if (fAccelPedal == 0.0f) {
      remoteState = 2.0f;
      speedRegulatorMode = 0.0f;
      fAccelPedal = 0.0f;
      speedCommand = fAccelPedal;
    } else {
      remoteState = 2.0f;
      speedRegulatorMode = 1.0f;
      fAccelPedal = vcuAped;
      speedCommand = fAccelPedal;
    }
    break;

  default:
    break;
  }

  throttleCmdFR = fRightMultiplier * fAccelPedal;
  throttleCmdFL = fLeftMultiplier * fAccelPedal;
  throttleCmdRR = fRightMultiplier * fAccelPedal;
  throttleCmdRL = fLeftMultiplier * fAccelPedal;

  sendAsiCmd();
}
