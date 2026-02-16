/**
 ******************************************************************************
 * @file           : vcu.c
 * @brief          : VCU application implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "vcu.h"
#include "canMessages.h"
#include "canOpen.h"
#include "canSignal.h"
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
  uint32_t txMailbox;

  txHeader.StdId = CAN_ID_DATA_DRIVE;
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = CAN_DLC_DATA_DRIVE;
  txHeader.TransmitGlobalTime = DISABLE;

  HAL_CAN_AddTxMessage(&hcan1, &txHeader, txBuf, &txMailbox);
}
