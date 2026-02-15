/**
 ******************************************************************************
 * @file           : steering.c
 * @brief          : Steering subsystem implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "steering.h"
#include "canOpen.h"
#include "yzaim.h"
#define steernode (uint8_t)1
/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize steering drive.
 *         Sets the mode of operation (0x6060) to Velocity mode on Node 1.
 */
void initSteering(void) {
  /* Set Mode of Operation: Index 0x6060, Sub 0x00, Node 1, 1 byte */
  SDO_Write(&hcan1, steernode, kxObjModesOfOperation, &kucModeVelocity);
  SDO_Write(&hcan1, steernode, kxObjControlWord, &allOperations);

  int32_t negativeSpeed = -100;
  SDO_Write(&hcan1, steernode, kxObjCommandDrive, &negativeSpeed);
}
