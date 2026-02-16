/**
 ******************************************************************************
 * @file           : yzaim.h
 * @brief          : YZAIM drive parameter definitions
 ******************************************************************************
 */

#ifndef __YZAIM_H
#define __YZAIM_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

#define kxObjModesOfOperation (uint16_t)0x6060, (uint8_t)0x00, (uint8_t)1
#define kxObjControlWord (uint16_t)0x6040, (uint8_t)0x00, (uint8_t)1
#define kxObjCommandDrive (uint16_t)0x60FF, (uint8_t)0x00, (uint8_t)1
#define kxObjReadAlarm (uint16_t)0x260E, (uint8_t)0x00, (uint8_t)1
#define kxObjPositionActualValue (uint16_t)0x6064, (uint8_t)0x00, (uint8_t)4
#define kxObjCommandDrive (uint16_t)0x60FF, (uint8_t)0x00, (uint8_t)4

/* Drive mode constants ------------------------------------------------------*/
static const uint8_t kucModeVelocity = 3;
static const uint8_t kucModePosition = 1;
static const uint8_t allOperations = 0x0F;
static const uint8_t disableOutputs = 0x06;
static const uint8_t clearFaults = 0x80;

#ifdef __cplusplus
}
#endif

#endif /* __YZAIM_H */
