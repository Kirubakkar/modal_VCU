/**
 ******************************************************************************
 * @file           : asi.h
 * @brief          : ASI traction motor controller definitions
 ******************************************************************************
 */

#ifndef __ASI_H
#define __ASI_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/******************************************************************************
 * Node IDs
 *****************************************************************************/
#define ASI_NODE_FR 0x2A
#define ASI_NODE_FL 0x2B
#define ASI_NODE_RR 0x2C
#define ASI_NODE_RL 0x2D

/******************************************************************************
 * CANopen Object Dictionary Entries
 *
 * Macro format: index, subIndex, dataLen, scalar
 * All entries use 2-byte expedited write (command byte 0x2B)
 *****************************************************************************/
/* Control loop */
#define xODEntrySpeedRegulatorKi                                               \
  (uint16_t)0x2000, (uint8_t)0x0B, (uint8_t)2, (float)256.0f
#define xODEntrySpeedRegulatorKp                                               \
  (uint16_t)0x2000, (uint8_t)0x0A, (uint8_t)2, (float)4096.0f

/* Motor & system ratings */
#define xODEntryRatedSystemVoltage                                             \
  (uint16_t)0x2001, (uint8_t)0x07, (uint8_t)2, (float)1.0f
#define xODEntrySensorMode                                                     \
  (uint16_t)0x2001, (uint8_t)0x0E, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorCurrent                                              \
  (uint16_t)0x2001, (uint8_t)0x08, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorSpeed                                                \
  (uint16_t)0x2001, (uint8_t)0x09, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorPowerRaceModePASPower                                \
  (uint16_t)0x2001, (uint8_t)0x3B, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorPowerRaceModeThrottlePower                           \
  (uint16_t)0x2001, (uint8_t)0x0A, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorPowerStreetModePASPower                              \
  (uint16_t)0x2001, (uint8_t)0x3A, (uint8_t)2, (float)1.0f
#define xODEntryRatedMotorPowerStreetModeThrottlePower                         \
  (uint16_t)0x2002, (uint8_t)0x04, (uint8_t)2, (float)1.0f
#define xODEntryNumberOfMotorPolePairs                                         \
  (uint16_t)0x2001, (uint8_t)0x0F, (uint8_t)2, (float)1.0f
#define xODEntryGearRatio                                                      \
  (uint16_t)0x2003, (uint8_t)0x23, (uint8_t)2, (float)256.0f

/* Voltage thresholds */
#define xODEntryFastOverVoltageThreshold                                       \
  (uint16_t)0x2002, (uint8_t)0x14, (uint8_t)2, (float)40.96f
#define xODEntryFastUnderVoltageThreshold                                      \
  (uint16_t)0x2002, (uint8_t)0x15, (uint8_t)2, (float)40.96f
#define xODEntrySlowOverVoltageThreshold                                       \
  (uint16_t)0x2002, (uint8_t)0x16, (uint8_t)2, (float)40.96f
#define xODEntrySlowUnderVoltageThreshold                                      \
  (uint16_t)0x2002, (uint8_t)0x17, (uint8_t)2, (float)40.96f

/* Battery foldback */
#define xODEntryHighBatteryFoldbackEndVoltage                                  \
  (uint16_t)0x2003, (uint8_t)0x04, (uint8_t)2, (float)40.96f
#define xODEntryHighBatteryFoldbackStartingVoltage                             \
  (uint16_t)0x2003, (uint8_t)0x03, (uint8_t)2, (float)40.96f
#define xODEntryLowBatteryFoldbackStartingVoltage                              \
  (uint16_t)0x2002, (uint8_t)0x0E, (uint8_t)2, (float)40.96f
#define xODEntryLowBatteryFoldbackEndVoltage                                   \
  (uint16_t)0x2002, (uint8_t)0x0F, (uint8_t)2, (float)40.96f
#define xODEntryColdBatteryFoldbackStartingTemperature                         \
  (uint16_t)0x2002, (uint8_t)0x10, (uint8_t)2, (float)1.0f
#define xODEntryColdBatteryFoldbackEndingTemperature                           \
  (uint16_t)0x2002, (uint8_t)0x11, (uint8_t)2, (float)1.0f

/* Current limits */
#define xODEntryBatteryCurrentLimit                                            \
  (uint16_t)0x2002, (uint8_t)0x1C, (uint8_t)2, (float)40.96f
#define xODEntryRegenerationBatteryCurrentLimit                                \
  (uint16_t)0x2002, (uint8_t)0x1D, (uint8_t)2, (float)40.96f
#define xODEntryMaximumBrakingTorque                                           \
  (uint16_t)0x2002, (uint8_t)0x1B, (uint8_t)2, (float)40.96f

/* Speed & torque ramps */
#define xODEntrySpeedLimitRampTime                                             \
  (uint16_t)0x2003, (uint8_t)0x3F, (uint8_t)2, (float)1.0f
#define xODEntrySpeedModePositiveAccelerationRamp                              \
  (uint16_t)0x2001, (uint8_t)0x35, (uint8_t)2, (float)16.0f
#define xODEntrySpeedModeRegenRamp                                             \
  (uint16_t)0x2001, (uint8_t)0x37, (uint8_t)2, (float)16.0f
#define xODEntryPositiveMotoringTorqueRamp                                     \
  (uint16_t)0x2003, (uint8_t)0x1D, (uint8_t)2, (float)1.0f
#define xODEntryNegativeMotoringTorqueRamp                                     \
  (uint16_t)0x2003, (uint8_t)0x1E, (uint8_t)2, (float)1.0f
#define xODEntryPositiveBrakingTorqueRamp                                      \
  (uint16_t)0x2003, (uint8_t)0x21, (uint8_t)2, (float)1.0f
#define xODEntryNegativeBrakingTorqueRamp                                      \
  (uint16_t)0x2003, (uint8_t)0x22, (uint8_t)2, (float)1.0f

/* Fault / flash commands */
#define xODEntryFaultClear                                                     \
  (uint16_t)0x2007, (uint8_t)0x3D, (uint8_t)2, (float)1.0f
#define xODEntryLoadFirmwareToFlash                                            \
  (uint16_t)0x2007, (uint8_t)0x3F, (uint8_t)2, (float)1.0f
#define xODEntryWriteParametersToFlash                                         \
  (uint16_t)0x2007, (uint8_t)0x40, (uint8_t)2, (float)1.0f

/******************************************************************************
 * Motor & Controller Parameters
 *****************************************************************************/
/* Motor controller */
static const float kfMotorControllerNomVoltage = 36.0f;
static const float kfMotorControllerKi = 5.0f;
static const float kfMotorControllerKp = 2.0f;

/* Motor ratings */
static const float kfMotorRatedCurrent = 70.0f;
static const float kfMotorRatedPower = 1000.0f;
static const float kfMotorRatedSpeed = 3000.0f;
static const uint8_t kucMotorMagnetPairs = 10;
static const float kfMotorGearRatio = 1.0f;

/* Voltage thresholds */
static const float kfMotorControllerFastOverVoltage = 120.8252f;
static const float kfMotorControllerFastUnderVoltage = 75.0f;
static const float kfMotorControllerSlowOverVoltage = 118.0420f;
static const float kfMotorControllerSlowUnderVoltage = 80.5420f;

/* Battery foldback */
static const float kfMotorControllerHighBatteryFoldbackEndVoltage = 112.0f;
static const float kfMotorControllerHighBatteryFoldbackStartingVoltage = 110.0f;
static const float kfMotorControllerLowBatteryFoldbackStartingVoltage = 88.0f;
static const float kfMotorControllerLowBatteryFoldbackEndVoltage = 84.0f;
static const float kfMotorControllerColdBatteryFoldbackStartingTemperature =
    3.0f;
static const float kfMotorControllerColdBatteryFoldbackEndingTemperature =
    -20.0f;

/* Current limits */
static const float kfBatteryCurrentLimit = 100.0f;
static const float kfRegenerationBatteryCurrentLimit = 56.25f;
static const float kfMaxBrakingTorque = 100.0f;

/* Speed & torque ramps */
static const float kfSpeedLimitRampTime = 0.0f;
static const float kfSpeedModePositiveAccelRamp = 1.0f;
static const float kfSpeedModeRegenRamp = 1.0f;
static const float kfPositiveMotorTorqueRamp = 1.0f;
static const float kfNegativeMotorTorqueRamp = 1.0f;
static const float kfPositiveBrakingTorqueRamp = 10.0f;
static const float kfNegativeBrakingTorqueRamp = 10.0f;

/******************************************************************************
 * Enumerations
 *****************************************************************************/
/* Remote state command */
#define ASI_REMOTE_STATE_OFF 0
#define ASI_REMOTE_STATE_IDLE 1
#define ASI_REMOTE_STATE_RUN 2

/* Speed regulator mode */
#define ASI_SPEED_REG_SPEED 0
#define ASI_SPEED_REG_TORQUE 1
#define ASI_SPEED_REG_TORQUE_SPEED 2

/* Sensor mode */
#define ASI_SENSOR_SENSORED 0
#define ASI_SENSOR_HYBRID 1
#define ASI_SENSOR_SENSORLESS 2

/******************************************************************************
 * Fault Bitmasks (Faults 1)
 *****************************************************************************/
#define ASI_FAULT_CONTROLLER_OVER_VOLT 0x0001
#define ASI_FAULT_FILTERED_PHASE_OVER_CURRENT 0x0002
#define ASI_FAULT_BAD_CURRENT_SENSOR_CAL 0x0004
#define ASI_FAULT_CURRENT_SENSOR_OVER_CURRENT 0x0008
#define ASI_FAULT_CONTROLLER_OVER_TEMPERATURE 0x0010
#define ASI_FAULT_MOTOR_HALL_SENSOR 0x0020
#define ASI_FAULT_CONTROLLER_UNDER_VOLT 0x0040
#define ASI_FAULT_POST_STATIC_GATING_TEST 0x0080
#define ASI_FAULT_NETWORK_COMM_TIMEOUT 0x0100
#define ASI_FAULT_INSTANT_PHASE_OVER_CURRENT 0x0200
#define ASI_FAULT_MOTOR_OVER_TEMPERATURE 0x0400
#define ASI_FAULT_THROTTLE_VOLT_RANGE 0x0800
#define ASI_FAULT_INSTANT_CONTROLLER_OVER_VOLT 0x1000
#define ASI_FAULT_INTERNAL_ERROR 0x2000
#define ASI_FAULT_POST_DYNAMIC_GATING_TEST 0x4000
#define ASI_FAULT_INSTANT_CONTROLLER_UNDER_VOLT 0x8000

/******************************************************************************
 * Fault Bitmasks (Faults 2)
 *****************************************************************************/
#define ASI_FAULT2_PARAMETER_CRC 0x0001
#define ASI_FAULT2_CURRENT_SCALING 0x0002
#define ASI_FAULT2_VOLT_SCALING 0x0004
#define ASI_FAULT2_HEADLIGHT_UNDER_VOLT 0x0008
#define ASI_FAULT2_RESERVED 0x0010
#define ASI_FAULT2_CAN_BUS 0x0020
#define ASI_FAULT2_HALL_STALL 0x0040
#define ASI_FAULT2_BOOTLOADER 0x0080
#define ASI_FAULT2_PARAMETER2_CRC 0x0100
#define ASI_FAULT2_HALL_VS_SENSORLESS_POS 0x0200
#define ASI_FAULT2_DYN_TORQUE_SENSOR_VOLT_RANGE 0x0400
#define ASI_FAULT2_DYN_TORQUE_SENSOR_STATIC_VOLT 0x0800
#define ASI_FAULT2_REMOTE_CAN_FAULT 0x1000
#define ASI_FAULT2_ACCEL_SIDE_TILT 0x2000
#define ASI_FAULT2_SPARE1 0x4000
#define ASI_FAULT2_SPARE2 0x8000

/******************************************************************************
 * Exported Functions
 *****************************************************************************/
void asiInit(void);
void asiNodeInit(uint8_t nodeId);

#ifdef __cplusplus
}
#endif

#endif /* __ASI_H */
