/**
 ******************************************************************************
 * @file           : steering.c
 * @brief          : Steering subsystem implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "steering.h"
#include "canOpen.h"
#include "cmsis_os.h"
#include "yzaim.h"
#include <math.h>

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Global variables ----------------------------------------------------------*/
float centerPosition = 0.0f;

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Calculate maximum steer ticks for the full lock-to-lock range.
 */
static float calculateMaxSteerTick(void) {
  float kulOutputMax = ((1 << ENCODER_BITS) - 1) * OUTPUT_GEAR_RATIO;
  float percentRotation = LOCK_TO_LOCK_ANGLE / 360.0f;
  return kulOutputMax * percentRotation;
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize steering drive - full homing sequence.
 *
 *         1. Set velocity mode
 *         2. Enable servo (controlword 0x0F)
 *         3. Send negative speed to move to physical end
 *         4. Poll alarm register via SDO_Read until value == 20
 *         5. Read actual position (home position, little-endian)
 *         6. Stop drive, disable outputs, clear faults
 *         7. Switch to position mode
 *         8. Calculate center position
 *
 * @retval 0 on success, 1 on failure
 */
int initSteering(void) {

  /* 1. Set Velocity mode */
  SDO_Write(&hcan1, STEER_NODE, kxObjModesOfOperation, &kucModeVelocity);
  osDelay(1000);

  /* 2. Enable the servo (Control Word: Enable + Allow operation) */
  SDO_Write(&hcan1, STEER_NODE, kxObjControlWord, &allOperations);
  osDelay(100);

  /* 3. Send NEGATIVE speed command to move to physical end */
  int32_t negativeSpeed = -100;
  SDO_Write(&hcan1, STEER_NODE, kxObjCommandDrive, &negativeSpeed);

  /* 4. Poll alarm register until value == 20 (physical resistance alarm)
   *    Timeout after ALARM_TIMEOUT_MS to avoid infinite loop */
  uint8_t alarmValue = 0;
  uint32_t elapsed = 0;

  while (elapsed < ALARM_TIMEOUT_MS) {
    SDO_Status_t status =
        SDO_Read(&hcan1, STEER_NODE, kxObjReadAlarm, &alarmValue);

    if (status == SDO_OK && alarmValue == ALARM_TARGET) {
      break;
    }

    osDelay(100);
    elapsed += 100;
  }

  /* Fail case: alarm not received within timeout */
  if (alarmValue != ALARM_TARGET) {
    SDO_Write(&hcan1, STEER_NODE, kxObjControlWord, &disableOutputs);
    return 1;
  }

  /* 5. Read the current position (home position) - 4 bytes little-endian */
  uint8_t posData[4] = {0};
  SDO_Status_t status =
      SDO_Read(&hcan1, STEER_NODE, kxObjPositionActualValue, posData);

  if (status != SDO_OK) {
    return 1;
  }

  int32_t homePosition =
      (int32_t)((uint32_t)posData[0] | ((uint32_t)posData[1] << 8) |
                ((uint32_t)posData[2] << 16) | ((uint32_t)posData[3] << 24));

  /* 6. Stop drive, disable outputs, clear faults */
  int32_t zeroSpeed = 0;
  SDO_Write(&hcan1, STEER_NODE, kxObjCommandDrive,
            (uint8_t *)&zeroSpeed); /* Stop drive      */
  SDO_Write(&hcan1, STEER_NODE, kxObjControlWord,
            &disableOutputs); /* Disable outputs */
  SDO_Write(&hcan1, STEER_NODE, kxObjControlWord,
            &clearFaults); /* Clear faults    */
  osDelay(1000);

  /* 7. Switch to Position Mode */
  SDO_Write(&hcan1, STEER_NODE, kxObjModesOfOperation, &kucModePosition);

  /* 8. Calculate center position = half the travel + home position */
  float maxSteerTicks = calculateMaxSteerTick();
  centerPosition = (maxSteerTicks / 2.0f) + (float)homePosition;

  /* Send initial position (0 degrees = center) */
  sendPosition(0.0f);

  return 0;
}

/**
 * @brief  Send a steering angle command via CAN (raw CAN frame on 0x201).
 *
 *         Converts angle (degrees) to encoder ticks, adds the center
 *         position offset, and sends as a raw CAN message.
 *
 * @param  angle  Steering angle in degrees (-37.1 to +37.1)
 */
void sendPosition(float angle) {
  int32_t position;

  if (angle > -MAX_STEER_ANGLE && angle < MAX_STEER_ANGLE) {
    position = (int32_t)(TICKS_PER_ANGLE * angle);
  } else {
    position = 0;
  }

  position = position + (int32_t)centerPosition;

  /* Build raw CAN frame on ID 0x201 */
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = 0x201;
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 8;
  txHeader.TransmitGlobalTime = DISABLE;

  uint8_t txData[8] = {0};
  txData[0] = 0x2F;
  txData[1] = 0x00;
  txData[2] = 0x01;
  txData[3] = (uint8_t)(position & 0xFF);
  txData[4] = (uint8_t)((position >> 8) & 0xFF);
  txData[5] = (uint8_t)((position >> 16) & 0xFF);
  txData[6] = (uint8_t)((position >> 24) & 0xFF);

  uint32_t txMailbox;
  if (HAL_CAN_GetTxMailboxesFreeLevel(&hcan1) > 0) {
    HAL_CAN_AddTxMessage(&hcan1, &txHeader, txData, &txMailbox);
  }
}
