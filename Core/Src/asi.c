/**
 ******************************************************************************
 * @file           : asi.c
 * @brief          : ASI traction motor controller implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "asi.h"
#include "canOpen.h"
#include "cmsis_os.h"

/* External variables --------------------------------------------------------*/
extern CAN_HandleTypeDef hcan1;

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize all 4 ASI motor controllers.
 *         Calls asiNodeInit() for each node (FR, FL, RR, RL).
 */
void asiInit(void) {
  asiNodeInit(ASI_NODE_FR);
  asiNodeInit(ASI_NODE_FL);
  asiNodeInit(ASI_NODE_RR);
  asiNodeInit(ASI_NODE_RL);
}

/**
 * @brief  Initialize a single ASI motor controller via SDO writes.
 * @param  nodeId  CANopen node ID of the motor controller
 */
void asiNodeInit(uint8_t nodeId) {
  uint16_t val16;

  /* Control loop */
  val16 = (uint16_t)kfMotorControllerKi;
  SDO_Write(&hcan1, nodeId, xODEntrySpeedRegulatorKi, (uint8_t *)&val16);
  val16 = (uint16_t)kfMotorControllerKp;
  SDO_Write(&hcan1, nodeId, xODEntrySpeedRegulatorKp, (uint8_t *)&val16);

  /* Motor & system ratings */
  val16 = (uint16_t)kfMotorControllerNomVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryRatedSystemVoltage, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorRatedPower;
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorPowerRaceModePASPower, (uint8_t *)&val16);
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorPowerRaceModeThrottlePower, (uint8_t *)&val16);
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorPowerStreetModePASPower, (uint8_t *)&val16);
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorPowerStreetModeThrottlePower, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorRatedCurrent;
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorCurrent, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorRatedSpeed;
  SDO_Write(&hcan1, nodeId, xODEntryRatedMotorSpeed, (uint8_t *)&val16);

  val16 = (uint16_t)kucMotorMagnetPairs;
  SDO_Write(&hcan1, nodeId, xODEntryNumberOfMotorPolePairs, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorGearRatio;
  SDO_Write(&hcan1, nodeId, xODEntryGearRatio, (uint8_t *)&val16);

  /* Voltage thresholds */
  val16 = (uint16_t)kfMotorControllerFastOverVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryFastOverVoltageThreshold, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerFastUnderVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryFastUnderVoltageThreshold, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerSlowOverVoltage;
  SDO_Write(&hcan1, nodeId, xODEntrySlowOverVoltageThreshold, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerSlowUnderVoltage;
  SDO_Write(&hcan1, nodeId, xODEntrySlowUnderVoltageThreshold, (uint8_t *)&val16);

  /* Battery foldback */
  val16 = (uint16_t)kfMotorControllerHighBatteryFoldbackEndVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryHighBatteryFoldbackEndVoltage, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerHighBatteryFoldbackStartingVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryHighBatteryFoldbackStartingVoltage, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerLowBatteryFoldbackStartingVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryLowBatteryFoldbackStartingVoltage, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerLowBatteryFoldbackEndVoltage;
  SDO_Write(&hcan1, nodeId, xODEntryLowBatteryFoldbackEndVoltage, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerColdBatteryFoldbackStartingTemperature;
  SDO_Write(&hcan1, nodeId, xODEntryColdBatteryFoldbackStartingTemperature, (uint8_t *)&val16);

  val16 = (uint16_t)kfMotorControllerColdBatteryFoldbackEndingTemperature;
  SDO_Write(&hcan1, nodeId, xODEntryColdBatteryFoldbackEndingTemperature, (uint8_t *)&val16);

  /* Current limits */
  val16 = (uint16_t)kfBatteryCurrentLimit;
  SDO_Write(&hcan1, nodeId, xODEntryBatteryCurrentLimit, (uint8_t *)&val16);

  val16 = (uint16_t)kfRegenerationBatteryCurrentLimit;
  SDO_Write(&hcan1, nodeId, xODEntryRegenerationBatteryCurrentLimit, (uint8_t *)&val16);

  val16 = (uint16_t)kfMaxBrakingTorque;
  SDO_Write(&hcan1, nodeId, xODEntryMaximumBrakingTorque, (uint8_t *)&val16);

  /* Speed & torque ramps */
  val16 = (uint16_t)kfSpeedLimitRampTime;
  SDO_Write(&hcan1, nodeId, xODEntrySpeedLimitRampTime, (uint8_t *)&val16);

  val16 = (uint16_t)kfSpeedModePositiveAccelRamp;
  SDO_Write(&hcan1, nodeId, xODEntrySpeedModePositiveAccelerationRamp, (uint8_t *)&val16);

  val16 = (uint16_t)kfSpeedModeRegenRamp;
  SDO_Write(&hcan1, nodeId, xODEntrySpeedModeRegenRamp, (uint8_t *)&val16);

  val16 = (uint16_t)kfPositiveMotorTorqueRamp;
  SDO_Write(&hcan1, nodeId, xODEntryPositiveMotoringTorqueRamp, (uint8_t *)&val16);

  val16 = (uint16_t)kfNegativeMotorTorqueRamp;
  SDO_Write(&hcan1, nodeId, xODEntryNegativeMotoringTorqueRamp, (uint8_t *)&val16);

  val16 = (uint16_t)kfPositiveBrakingTorqueRamp;
  SDO_Write(&hcan1, nodeId, xODEntryPositiveBrakingTorqueRamp, (uint8_t *)&val16);

  val16 = (uint16_t)kfNegativeBrakingTorqueRamp;
  SDO_Write(&hcan1, nodeId, xODEntryNegativeBrakingTorqueRamp, (uint8_t *)&val16);
}
