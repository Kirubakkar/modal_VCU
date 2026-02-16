/**
  ******************************************************************************
  * @file           : steering.h
  * @brief          : Steering subsystem header
  ******************************************************************************
  */

#ifndef __STEERING_H
#define __STEERING_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>

/* Steering configuration ----------------------------------------------------*/
#define STEER_NODE        (uint8_t)1
#define ALARM_TARGET      20       /* Physical resistance alarm value */
#define ALARM_TIMEOUT_MS  10000    /* 10 seconds timeout for homing   */

/* Steering geometry constants -----------------------------------------------*/
#define ENCODER_BITS           15
#define SERVO_MAX_ENCODER      ((1 << ENCODER_BITS) - 1)  /* 32767 */
#define OUTPUT_GEAR_RATIO      35.0f
#define LOCK_TO_LOCK_ANGLE     74.2f    /* Degrees total (37.1 * 2) */
#define MAX_STEER_ANGLE        37.1f    /* Degrees in each direction */

/* Derived constants ---------------------------------------------------------*/
#define OUTPUT_MAX_ENCODER     (SERVO_MAX_ENCODER * OUTPUT_GEAR_RATIO)
#define MAX_STEER_ANGLE_TICK   (OUTPUT_MAX_ENCODER * (LOCK_TO_LOCK_ANGLE / 360.0f))
#define MIN_STEER_ANGLE_TICK   0.0f
#define TICKS_PER_ANGLE        (MAX_STEER_ANGLE_TICK / LOCK_TO_LOCK_ANGLE)

/* Exported variables --------------------------------------------------------*/
extern float centerPosition;

/* Exported functions prototypes ---------------------------------------------*/

/**
  * @brief  Initialize steering drive - homing sequence + center calculation.
  * @retval 0 on success, 1 on failure
  */
int initSteering(void);

/**
  * @brief  Send a steering angle command via CAN.
  * @param  angle  Steering angle in degrees (-37.1 to +37.1)
  */
void sendPosition(float angle);

#ifdef __cplusplus
}
#endif

#endif /* __STEERING_H */
