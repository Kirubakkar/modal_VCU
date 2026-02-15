/**
  ******************************************************************************
  * @file           : vcu.c
  * @brief          : VCU application implementation
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "vcu.h"
#include "canOpen.h"
#include "steering.h"

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Exported functions --------------------------------------------------------*/

/**
  * @brief  Initialize VCU - sends initial SDO commands to configure drives.
  *         Must be called after CAN peripheral is started.
  *
  *         Sends SDO Write to Node 1, Index 0x6040, SubIndex 0x00, Data = 0x01
  *         (CiA 402 Controlword: Shutdown command)
  */
void initVCU(void)
{
  /* Initialize steering subsystem */
  initSteering();
}
