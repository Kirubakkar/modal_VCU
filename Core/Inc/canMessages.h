/**
 ******************************************************************************
 * @file           : canMessages.h
 * @brief          : CAN identifier, DLC, period, and signal definitions
 *
 *                   Ported from can_messages.hpp (C++ reference)
 ******************************************************************************
 */

#ifndef __CAN_MESSAGES_H
#define __CAN_MESSAGES_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "canSignal.h"

/******************************************************************************
 * General Constants
 *****************************************************************************/
/* Periods (ms) */
#define CAN_PERIOD_MS_10       10
#define CAN_PERIOD_MS_100      100
#define CAN_PERIOD_MS_1000     1000
#define CAN_PERIOD_MS_10000    10000

/* Base ID */
#define CAN_ID_BASE_MODAL      0x200

/******************************************************************************
 * Command Identifiers (offsets)
 *****************************************************************************/
#define CAN_ID_BASE_CMD_POWER             0x10
#define CAN_ID_BASE_CMD_RELAY_CONTROL     0x11
#define CAN_ID_BASE_CMD_DRIVE             0x20
#define CAN_ID_BASE_CMD_INDIV_AXLE        0x21
#define CAN_ID_BASE_CMD_AXLE_F            0x22
#define CAN_ID_BASE_CMD_AXLE_R            0x23
#define CAN_ID_BASE_CMD_WHEEL_RPM         0x24
#define CAN_ID_BASE_CMD_WHEEL_ENCODER_F   0x25
#define CAN_ID_BASE_CMD_WHEEL_ENCODER_R   0x26
#define CAN_ID_BASE_CMD_WHEEL_CURRENT     0x27
#define CAN_ID_BASE_CMD_MECANUM_CONFIG    0x29
#define CAN_ID_BASE_CMD_MECANUM_FR        0x2A
#define CAN_ID_BASE_CMD_MECANUM_FL        0x2B
#define CAN_ID_BASE_CMD_MECANUM_RR        0x2C
#define CAN_ID_BASE_CMD_MECANUM_RL        0x2D
#define CAN_ID_BASE_CMD_TWIST             0x2E
#define CAN_ID_BASE_CMD_LIGHT             0x60
#define CAN_ID_BASE_CMD_LOCK_F            0x70
#define CAN_ID_BASE_CMD_LOCK_R            0x80

#define CAN_ID_BASE_CONFIG_AXLE           0xD0
#define CAN_ID_BASE_CONFIG_MECH_BRAKE_F   0xD1
#define CAN_ID_BASE_CONFIG_MECH_BRAKE_R   0xD2

#define CAN_ID_BASE_DIAGNOSE_FRAME        0xE0
#define CAN_ID_BASE_DIAGNOSE_AXLE_F       0xE1
#define CAN_ID_BASE_DIAGNOSE_AXLE_R       0xE2
#define CAN_ID_BASE_DIAGNOSE_RC           0xE3
#define CAN_ID_BASE_FAULT_CLEAR           0xE4

/* Command Identifiers (full) */
#define CAN_ID_CMD_POWER            (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_POWER)
#define CAN_ID_CMD_RELAY_CONTROL    (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_RELAY_CONTROL)
#define CAN_ID_CMD_DRIVE            (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_DRIVE)
#define CAN_ID_CMD_INDIV_AXLE       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_INDIV_AXLE)
#define CAN_ID_CMD_AXLE_F           (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_AXLE_F)
#define CAN_ID_CMD_AXLE_R           (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_AXLE_R)
#define CAN_ID_CMD_WHEEL_RPM        (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_WHEEL_RPM)
#define CAN_ID_CMD_WHEEL_ENCODER_F  (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_WHEEL_ENCODER_F)
#define CAN_ID_CMD_WHEEL_ENCODER_R  (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_WHEEL_ENCODER_R)
#define CAN_ID_CMD_WHEEL_CURRENT    (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_WHEEL_CURRENT)
#define CAN_ID_CMD_MECANUM_CONFIG   (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_MECANUM_CONFIG)
#define CAN_ID_CMD_MECANUM_FR       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_MECANUM_FR)
#define CAN_ID_CMD_MECANUM_FL       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_MECANUM_FL)
#define CAN_ID_CMD_MECANUM_RR       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_MECANUM_RR)
#define CAN_ID_CMD_MECANUM_RL       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_MECANUM_RL)
#define CAN_ID_CMD_TWIST            (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_TWIST)
#define CAN_ID_CMD_LIGHT            (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_LIGHT)
#define CAN_ID_CMD_LOCK_F           (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_LOCK_F)
#define CAN_ID_CMD_LOCK_R           (CAN_ID_BASE_MODAL + CAN_ID_BASE_CMD_LOCK_R)

#define CAN_ID_CONFIG_AXLE          (CAN_ID_BASE_MODAL + CAN_ID_BASE_CONFIG_AXLE)
#define CAN_ID_CONFIG_MECH_BRAKE_F  (CAN_ID_BASE_MODAL + CAN_ID_BASE_CONFIG_MECH_BRAKE_F)
#define CAN_ID_CONFIG_MECH_BRAKE_R  (CAN_ID_BASE_MODAL + CAN_ID_BASE_CONFIG_MECH_BRAKE_R)

#define CAN_ID_DIAGNOSE_FRAME       (CAN_ID_BASE_MODAL + CAN_ID_BASE_DIAGNOSE_FRAME)
#define CAN_ID_DIAGNOSE_AXLE_F      (CAN_ID_BASE_MODAL + CAN_ID_BASE_DIAGNOSE_AXLE_F)
#define CAN_ID_DIAGNOSE_AXLE_R      (CAN_ID_BASE_MODAL + CAN_ID_BASE_DIAGNOSE_AXLE_R)
#define CAN_ID_DIAGNOSE_RC          (CAN_ID_BASE_MODAL + CAN_ID_BASE_DIAGNOSE_RC)
#define CAN_ID_FAULT_CLEAR          (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_CLEAR)

/******************************************************************************
 * Data Identifiers (offsets)
 *****************************************************************************/
#define CAN_ID_BASE_FAULT_GEN              0x00
#define CAN_ID_BASE_FAULT_AXLE             0x01
#define CAN_ID_BASE_FAULT_RC               0x02
#define CAN_ID_BASE_FAULT_HMI              0x0F
#define CAN_ID_BASE_DATA_POWER             0x30
#define CAN_ID_BASE_DATA_RELAY_CONTROL     0x31
#define CAN_ID_BASE_DATA_DRIVE             0x40
#define CAN_ID_BASE_DATA_WHEEL_KPH         0x41
#define CAN_ID_BASE_DATA_AXLE_F            0x42
#define CAN_ID_BASE_DATA_AXLE_R            0x43
#define CAN_ID_BASE_DATA_WHEEL_RPM         0x44
#define CAN_ID_BASE_DATA_WHEEL_ENCODER_F   0x45
#define CAN_ID_BASE_DATA_WHEEL_ENCODER_R   0x46
#define CAN_ID_BASE_DATA_WHEEL_POWER_F     0x47
#define CAN_ID_BASE_DATA_WHEEL_POWER_R     0x48
#define CAN_ID_BASE_DATA_MECANUM_STATUS    0x49
#define CAN_ID_BASE_DATA_AXLE_F_WHEEL_KPH 0x4A
#define CAN_ID_BASE_DATA_AXLE_R_WHEEL_KPH 0x4B
#define CAN_ID_BASE_DATA_BATTERY_POWER     0x50
#define CAN_ID_BASE_DATA_BATTERY_STATE     0x51
#define CAN_ID_BASE_DATA_LIGHT             0x90
#define CAN_ID_BASE_DATA_LOCK_F            0xA0
#define CAN_ID_BASE_DATA_LOCK_R            0xB0

#define CAN_ID_BASE_BEAT_FRAME             0xF0
#define CAN_ID_BASE_SW_VERSION_FRAME       0xF1
#define CAN_ID_BASE_BEAT_AXLE_F            0xF2
#define CAN_ID_BASE_SW_VERSION_AXLE_F      0xF3
#define CAN_ID_BASE_BEAT_RC                0xF4
#define CAN_ID_BASE_SW_VERSION_RC          0xF5
#define CAN_ID_BASE_CAN_HEALTH_FRAME       0xF6
#define CAN_ID_BASE_CAN_HEALTH_FRONT       0xF7
#define CAN_ID_BASE_CAN_HEALTH_REAR        0xF8
#define CAN_ID_BASE_FEATURE_ENABLE         0xF9
#define CAN_ID_BASE_ACTIVE_CAL             0xFA

#define CAN_ID_BASE_FAULT_HIST_MOTOR_FR    0xFC
#define CAN_ID_BASE_FAULT_HIST_MOTOR_FL    0xFD
#define CAN_ID_BASE_FAULT_HIST_MOTOR_RR    0xFE
#define CAN_ID_BASE_FAULT_HIST_MOTOR_RL    0xFF

/* Data Identifiers (full) */
#define CAN_ID_FAULT_GEN             (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_GEN)
#define CAN_ID_FAULT_AXLE            (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_AXLE)
#define CAN_ID_FAULT_RC              (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_RC)
#define CAN_ID_FAULT_HMI             (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_HMI)
#define CAN_ID_DATA_POWER            (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_POWER)
#define CAN_ID_DATA_RELAY_CONTROL    (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_RELAY_CONTROL)
#define CAN_ID_DATA_DRIVE            (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_DRIVE)
#define CAN_ID_DATA_WHEEL_KPH        (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_KPH)
#define CAN_ID_DATA_AXLE_F           (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_AXLE_F)
#define CAN_ID_DATA_AXLE_R           (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_AXLE_R)
#define CAN_ID_DATA_WHEEL_RPM        (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_RPM)
#define CAN_ID_DATA_WHEEL_ENCODER_F  (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_ENCODER_F)
#define CAN_ID_DATA_WHEEL_ENCODER_R  (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_ENCODER_R)
#define CAN_ID_DATA_WHEEL_POWER_F    (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_POWER_F)
#define CAN_ID_DATA_WHEEL_POWER_R    (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_WHEEL_POWER_R)
#define CAN_ID_DATA_MECANUM_STATUS   (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_MECANUM_STATUS)
#define CAN_ID_DATA_AXLE_F_WHEEL_KPH (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_AXLE_F_WHEEL_KPH)
#define CAN_ID_DATA_AXLE_R_WHEEL_KPH (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_AXLE_R_WHEEL_KPH)
#define CAN_ID_DATA_BATTERY_POWER    (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_BATTERY_POWER)
#define CAN_ID_DATA_BATTERY_STATE    (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_BATTERY_STATE)
#define CAN_ID_DATA_LIGHT            (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_LIGHT)
#define CAN_ID_DATA_LOCK_F           (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_LOCK_F)
#define CAN_ID_DATA_LOCK_R           (CAN_ID_BASE_MODAL + CAN_ID_BASE_DATA_LOCK_R)

#define CAN_ID_BEAT_FRAME            (CAN_ID_BASE_MODAL + CAN_ID_BASE_BEAT_FRAME)
#define CAN_ID_SW_VERSION_FRAME      (CAN_ID_BASE_MODAL + CAN_ID_BASE_SW_VERSION_FRAME)
#define CAN_ID_BEAT_AXLE_F           (CAN_ID_BASE_MODAL + CAN_ID_BASE_BEAT_AXLE_F)
#define CAN_ID_SW_VERSION_AXLE_F     (CAN_ID_BASE_MODAL + CAN_ID_BASE_SW_VERSION_AXLE_F)
#define CAN_ID_BEAT_RC               (CAN_ID_BASE_MODAL + CAN_ID_BASE_BEAT_RC)
#define CAN_ID_SW_VERSION_RC         (CAN_ID_BASE_MODAL + CAN_ID_BASE_SW_VERSION_RC)
#define CAN_ID_CAN_HEALTH_FRAME      (CAN_ID_BASE_MODAL + CAN_ID_BASE_CAN_HEALTH_FRAME)
#define CAN_ID_CAN_HEALTH_FRONT      (CAN_ID_BASE_MODAL + CAN_ID_BASE_CAN_HEALTH_FRONT)
#define CAN_ID_CAN_HEALTH_REAR       (CAN_ID_BASE_MODAL + CAN_ID_BASE_CAN_HEALTH_REAR)
#define CAN_ID_FEATURE_ENABLE        (CAN_ID_BASE_MODAL + CAN_ID_BASE_FEATURE_ENABLE)
#define CAN_ID_ACTIVE_CAL            (CAN_ID_BASE_MODAL + CAN_ID_BASE_ACTIVE_CAL)

#define CAN_ID_FAULT_HIST_MOTOR_FR   (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_HIST_MOTOR_FR)
#define CAN_ID_FAULT_HIST_MOTOR_FL   (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_HIST_MOTOR_FL)
#define CAN_ID_FAULT_HIST_MOTOR_RR   (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_HIST_MOTOR_RR)
#define CAN_ID_FAULT_HIST_MOTOR_RL   (CAN_ID_BASE_MODAL + CAN_ID_BASE_FAULT_HIST_MOTOR_RL)

/* Non-standard Identifiers */
#define CAN_ID_BEAT_USER0            0x700
#define CAN_ID_BEAT_USER1            0x701
#define CAN_ID_BEAT_USER2            0x702
#define CAN_ID_BEAT_USER3            0x703
#define CAN_ID_RC_STATUS             0x7FE

/* ASI Feedback IDs */
#define CAN_ID_ASI_FEEDBACK_FR       0x23C
#define CAN_ID_ASI_FEEDBACK_FL       0x23D
#define CAN_ID_ASI_FEEDBACK_RR       0x23E
#define CAN_ID_ASI_FEEDBACK_RL       0x23F

/******************************************************************************
 * DLC
 *****************************************************************************/
#define CAN_DLC_DEFAULT              8

#define CAN_DLC_CMD_POWER            8
#define CAN_DLC_CMD_RELAY_CONTROL    8
#define CAN_DLC_CMD_DRIVE            8
#define CAN_DLC_CMD_INDIV_AXLE       8
#define CAN_DLC_CMD_AXLE_F           8
#define CAN_DLC_CMD_AXLE_R           8
#define CAN_DLC_CMD_WHEEL_RPM        8
#define CAN_DLC_CMD_WHEEL_ENCODER    8
#define CAN_DLC_CMD_WHEEL_CURRENT    8
#define CAN_DLC_CMD_MECANUM_CONFIG   8
#define CAN_DLC_CMD_MECANUM_FR       8
#define CAN_DLC_CMD_MECANUM_FL       8
#define CAN_DLC_CMD_MECANUM_RR       8
#define CAN_DLC_CMD_MECANUM_RL       8
#define CAN_DLC_CMD_TWIST            8
#define CAN_DLC_CMD_LIGHT            8
#define CAN_DLC_CMD_LOCK_F           8
#define CAN_DLC_CMD_LOCK_R           8

#define CAN_DLC_CONFIG_AXLE          8
#define CAN_DLC_CONFIG_MECH_BRAKE_F  8
#define CAN_DLC_CONFIG_MECH_BRAKE_R  8

#define CAN_DLC_DIAGNOSE_FRAME       8
#define CAN_DLC_DIAGNOSE_AXLE_F      8
#define CAN_DLC_DIAGNOSE_AXLE_R      8
#define CAN_DLC_FAULT_CLEAR          8

#define CAN_DLC_FAULT_GEN            8
#define CAN_DLC_FAULT_AXLE           8
#define CAN_DLC_FAULT_RC             8
#define CAN_DLC_FAULT_HMI            8
#define CAN_DLC_DATA_POWER           8
#define CAN_DLC_DATA_RELAY_CONTROL   8
#define CAN_DLC_DATA_DRIVE           8
#define CAN_DLC_DATA_WHEEL_KPH       8
#define CAN_DLC_DATA_AXLE_F          8
#define CAN_DLC_DATA_AXLE_R          8
#define CAN_DLC_DATA_WHEEL_RPM       8
#define CAN_DLC_DATA_WHEEL_ENCODER   8
#define CAN_DLC_DATA_WHEEL_POWER     8
#define CAN_DLC_DATA_MECANUM_STATUS  8
#define CAN_DLC_DATA_AXLE_F_WHEEL_KPH 8
#define CAN_DLC_DATA_AXLE_R_WHEEL_KPH 8
#define CAN_DLC_DATA_BATTERY_POWER   8
#define CAN_DLC_DATA_BATTERY_STATE   8
#define CAN_DLC_DATA_LIGHT           8
#define CAN_DLC_DATA_LOCK_F          8
#define CAN_DLC_DATA_LOCK_R          8

#define CAN_DLC_BEAT                 8
#define CAN_DLC_SW_VERSION           8
#define CAN_DLC_CAN_HEALTH           8
#define CAN_DLC_FEATURE_ENABLE       8
#define CAN_DLC_ACTIVE_CAL           8
#define CAN_DLC_FAULT_HIST_MOTOR     8

/******************************************************************************
 * Periods (ms)
 *****************************************************************************/
/* Command periods */
#define CAN_PERIOD_MS_CMD_POWER            CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_RELAY_CONTROL    CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_CMD_DRIVE            CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_INDIV_AXLE       CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_AXLE_F           CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_AXLE_R           CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_WHEEL_RPM        CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_WHEEL_ENCODER    CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_WHEEL_CURRENT    CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_MECANUM_CONFIG   CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_MECANUM_FR       CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_MECANUM_FL       CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_MECANUM_RR       CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_MECANUM_RL       CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_TWIST            CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_CMD_LIGHT            CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_CMD_LOCK_F           CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_CMD_LOCK_R           CAN_PERIOD_MS_100

#define CAN_PERIOD_MS_CONFIG_AXLE          CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_CONFIG_MECH_BRAKE_F  CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_CONFIG_MECH_BRAKE_R  CAN_PERIOD_MS_1000

#define CAN_PERIOD_MS_DIAGNOSE_FRAME       CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_DIAGNOSE_AXLE_F      CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_DIAGNOSE_AXLE_R      CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_FAULT_CLEAR          CAN_PERIOD_MS_1000

/* Data periods */
#define CAN_PERIOD_MS_FAULT_GEN            CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_FAULT_AXLE           CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_FAULT_RC             CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_FAULT_HMI            CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_POWER           CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_DATA_RELAY_CONTROL   CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_DATA_DRIVE           CAN_PERIOD_MS_10
#define CAN_PERIOD_MS_DATA_WHEEL_KPH       CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_AXLE_F          CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_AXLE_R          CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_WHEEL_RPM       CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_WHEEL_ENCODER   CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_WHEEL_POWER     CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_MECANUM_STATUS  CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_AXLE_F_WHEEL_KPH CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_AXLE_R_WHEEL_KPH CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_BATTERY_POWER   CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_DATA_BATTERY_STATE   CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_LIGHT           CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_LOCK_F          CAN_PERIOD_MS_100
#define CAN_PERIOD_MS_DATA_LOCK_R          CAN_PERIOD_MS_100

#define CAN_PERIOD_MS_BEAT                 CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_SW_VERSION           CAN_PERIOD_MS_10000
#define CAN_PERIOD_MS_CAN_HEALTH           CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_FEATURE_ENABLE       CAN_PERIOD_MS_1000
#define CAN_PERIOD_MS_ACTIVE_CAL           CAN_PERIOD_MS_10000
#define CAN_PERIOD_MS_FAULT_HIST_MOTOR     CAN_PERIOD_MS_1000

/* Communication timeout */
#define CAN_PERIOD_MS_TIMEOUT_COMMS  (CAN_PERIOD_MS_CMD_DRIVE * 2)

/******************************************************************************
 * Signals
 *
 * CanSignal_TypeDef: {scaler, offset, start_bit, length, little_endian, signed, float}
 *****************************************************************************/

/* --- CAN_ID_FAULT_GEN --- */
static const CanSignal_TypeDef kxCanSignalEstopCmd =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalEstopCommFrameUser =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalEstopTrig =
    {1, 0, 2, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommUser0 =
    {1, 0, 16, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommUser1 =
    {1, 0, 17, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommUser2 =
    {1, 0, 18, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommUser3 =
    {1, 0, 19, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommAxleF =
    {1, 0, 20, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommAxleR =
    {1, 0, 21, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommBms =
    {1, 0, 22, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultFrameCommRc =
    {1, 0, 23, 1, 1, 0, 0};

/* --- CAN_ID_FAULT_AXLE --- */
static const CanSignal_TypeDef kxCanSignalErrSteerInitF =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrSteerInitR =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrPrechargeLowVolt =
    {1, 0, 2, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrPrechargeTimeoutPrechgRelay =
    {1, 0, 3, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrPrechargeTimeoutMainRelay =
    {1, 0, 4, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrMotorVoltDiff =
    {1, 0, 5, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommEcuFrame =
    {1, 0, 8, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommBms =
    {1, 0, 9, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommBrakesF =
    {1, 0, 10, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommBrakesR =
    {1, 0, 11, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommSteerF =
    {1, 0, 12, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommSteerR =
    {1, 0, 13, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrFaultMotorFr =
    {1, 0, 14, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrFaultMotorFl =
    {1, 0, 15, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrFaultMotorRr =
    {1, 0, 16, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrFaultMotorRl =
    {1, 0, 17, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommLockerF =
    {1, 0, 18, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommLockerR =
    {1, 0, 19, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommMotorFr =
    {1, 0, 20, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommMotorFl =
    {1, 0, 21, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommMotorRr =
    {1, 0, 22, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommMotorRl =
    {1, 0, 23, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommUser0 =
    {1, 0, 24, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommUser1 =
    {1, 0, 25, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommUser2 =
    {1, 0, 26, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommUser3 =
    {1, 0, 27, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultCommRc =
    {1, 0, 28, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSpeedBadFr =
    {1, 0, 32, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSpeedBadFl =
    {1, 0, 33, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSpeedBadRr =
    {1, 0, 34, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSpeedBadRl =
    {1, 0, 35, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMotorVoltBadFr =
    {1, 0, 36, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMotorVoltBadFl =
    {1, 0, 37, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMotorVoltBadRr =
    {1, 0, 38, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMotorVoltBadRl =
    {1, 0, 39, 1, 1, 0, 0};

/* --- CAN_ID_FAULT_RC --- */
static const CanSignal_TypeDef kxCanSignalFaultRcCtrlConflict =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommFrame =
    {1, 0, 16, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommAxleF =
    {1, 0, 17, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommAxleR =
    {1, 0, 18, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommBms =
    {1, 0, 19, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommUser0 =
    {1, 0, 20, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommUser1 =
    {1, 0, 21, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommUser2 =
    {1, 0, 22, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultRcCommUser3 =
    {1, 0, 23, 1, 1, 0, 0};

/* --- CAN_ID_FAULT_HMI --- */
static const CanSignal_TypeDef kxCanSignalFaultHmiMil =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHmiContact =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHmiLimpHome =
    {1, 0, 2, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHmiStopSafelyNow =
    {1, 0, 3, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHmiStopNow =
    {1, 0, 4, 1, 1, 0, 0};

/* --- CAN_ID_*_POWER --- */
static const CanSignal_TypeDef kxCanSignalShutdown =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalPlatformOff =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalUserOff =
    {1, 0, 2, 1, 1, 0, 0};

/* --- CAN_ID_*_RELAY_CONTROL --- */
static const CanSignal_TypeDef kxCanSignalMainRelayCmd =
    {1, 0, 0, 1, 1, 0, 0};

/* --- CAN_ID_*_DRIVE, CAN_ID_DATA_AXLE_* --- */
static const CanSignal_TypeDef kxCanSignalAped =             /* Accelerator pedal 0.0:100.0 */
    {0.0625f, 0, 0, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBped =             /* Brake pedal 0.0:100.0 */
    {0.0625f, 0, 16, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerAng =         /* Steering angle -90.00:90.00 */
    {0.0078125f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalPrnd =             /* PRND Gear */
    {1, 0, 48, 2, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalEstopMode =        /* Estop Mode */
    {1, 0, 50, 2, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalDriveMode =        /* Drive mode */
    {1, 0, 52, 4, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerMode =        /* Steering mode */
    {1, 0, 56, 4, 1, 0, 0};

/* --- CAN_ID_CMD_INDIV_AXLE --- */
static const CanSignal_TypeDef kxCanSignalBpedF =            /* Front brake pedal 0.0:100.0 */
    {0.0625f, 0, 0, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerAngF =        /* Front steering angle -90.00:90.00 */
    {0.0078125f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalBpedR =            /* Rear brake pedal 0.0:100.0 */
    {0.0625f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerAngR =        /* Rear steering angle -90.00:90.00 */
    {0.0078125f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_*_AXLE_* (data feedback) --- */
static const CanSignal_TypeDef kxCanSignalWhlSpdKphR =       /* Right wheel speed KPH -100.00:100.00 */
    {0.0078125f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdKphL =       /* Left wheel speed KPH -100.00:100.00 */
    {0.0078125f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalBrakeInd =         /* Brake percentage 0.0:100.0 */
    {0.0625f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerAngInd =      /* Steering angle -90.00:90.00 */
    {0.0078125f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_*_WHEEL_KPH, CAN_ID_DATA_AXLE_*_WHEEL_KPH --- */
static const CanSignal_TypeDef kxCanSignalWhlSpdFR =         /* Front right -100.00:100.00 */
    {0.0078125f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdFL =         /* Front left -100.00:100.00 */
    {0.0078125f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdRR =         /* Rear right -100.00:100.00 */
    {0.0078125f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdRL =         /* Rear left -100.00:100.00 */
    {0.0078125f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_*_WHEEL_ENCODER_* --- */
static const CanSignal_TypeDef kxCanSignalWheelEncoderR =    /* Right encoder -2147483648:2147483647 */
    {1, 0, 0, 32, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWheelEncoderL =    /* Left encoder -2147483648:2147483647 */
    {1, 0, 32, 32, 1, 1, 0};

/* --- CAN_ID_*_WHEEL_RPM --- */
static const CanSignal_TypeDef kxCanSignalWhlSpdRpmFR =      /* Front right RPM -2500:2500 */
    {1, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdRpmFL =      /* Front left RPM -2500:2500 */
    {1, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdRpmRR =      /* Rear right RPM -2500:2500 */
    {1, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlSpdRpmRL =      /* Rear left RPM -2500:2500 */
    {1, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_CMD_WHEEL_CURRENT --- */
static const CanSignal_TypeDef kxCanSignalWhlCurrentFR =     /* Front right current -100:100 */
    {0.1f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlCurrentFL =     /* Front left current -100:100 */
    {0.1f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlCurrentRR =     /* Rear right current -100:100 */
    {0.1f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlCurrentRL =     /* Rear left current -100:100 */
    {0.1f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_DATA_WHEEL_POWER_* --- */
static const CanSignal_TypeDef kxCanSignalWhlCurrentR =      /* Right motor current */
    {1, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlCurrentL =      /* Left motor current */
    {1, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalWhlVoltageR =      /* Right motor voltage */
    {1, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalWhlVoltageL =      /* Left motor voltage */
    {1, 0, 48, 16, 1, 0, 0};

/* --- CAN_ID_*_MECANUM_* (status) --- */
static const CanSignal_TypeDef kxCanSignalMecanumStateF =    /* Front mecanum controller state */
    {1, 0, 0, 4, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMecanumStateR =    /* Rear mecanum controller state */
    {1, 0, 8, 4, 1, 0, 0};

/* --- CAN_ID_CMD_MECANUM_* --- */
static const CanSignal_TypeDef kxCanSignalMecanumState =     /* Mecanum controller state */
    {1, 0, 0, 4, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMecanumMode =      /* Mecanum operating mode */
    {1, 0, 4, 4, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalMecanumRpm =       /* Mecanum RPM -2000:2000 */
    {1, 0, 8, 12, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalMecanumCurrent =   /* Mecanum current -100:100 */
    {1, 0, 20, 12, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalMecanumEncoder =   /* Mecanum encoder */
    {1, 0, 32, 32, 1, 1, 0};

/* --- CAN_ID_CMD_TWIST --- */
static const CanSignal_TypeDef kxCanSignalTwistLinearX =     /* Linear X -12:12 m/s */
    {0.1f, 12.0f, 0, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTwistLinearY =     /* Linear Y -12:12 m/s */
    {0.1f, 12.0f, 8, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTwistLinearZ =     /* Linear Z -12:12 m/s */
    {0.1f, 12.0f, 16, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTwistAngularX =    /* Angular X -12:12 rad/s */
    {0.1f, 12.0f, 24, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTwistAngularY =    /* Angular Y -12:12 rad/s */
    {0.1f, 12.0f, 32, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTwistAngularZ =    /* Angular Z -12:12 rad/s */
    {0.1f, 12.0f, 40, 8, 1, 1, 0};

/* --- ASI State --- */
static const CanSignal_TypeDef kxCanSignalAsiState =         /* ASI remote state command */
    {1, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiSpeedMode =     /* ASI speed regulator mode */
    {1, 0, 16, 16, 1, 1, 0};

/* --- ASI Command --- */
static const CanSignal_TypeDef kxCanSignalAsiMaxMotorCurrent = /* ASI max motor current */
    {1.0f/40.96f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiMaxBrakeCurrent = /* ASI max brake current */
    {1.0f/40.96f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiTorqueCommand =   /* ASI torque command */
    {1.0f/40.96f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiSpeedCommand =    /* ASI speed command */
    {1.0f/40.96f, 0, 48, 16, 1, 1, 0};

/* --- ASI Beat --- */
static const CanSignal_TypeDef kxCanSignalAsiFaults1 =       /* ASI faults 1 */
    {1.0f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiFaults2 =       /* ASI faults 2 */
    {1.0f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiControllerTemp = /* ASI controller temp */
    {1.0f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiDspTemp =       /* ASI DSP temp */
    {1.0f, 0, 48, 16, 1, 1, 0};

/* --- ASI Feedback --- */
static const CanSignal_TypeDef kxCanSignalAsiMeasuredWheelRpm = /* ASI measured RPM */
    {1.0f/16.0f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiRawBatteryVolt =  /* ASI raw battery voltage */
    {1.0f/4096.0f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiBatteryCurrent =  /* ASI battery current */
    {1.0f/32.0f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalAsiMotorCurrent =    /* ASI motor current */
    {1.0f/32.0f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_*_LIGHT --- */
static const CanSignal_TypeDef kxCanSignalTurnR =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalTurnL =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalHazard =
    {1, 0, 2, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalHeadlight =
    {1, 0, 3, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakelight =
    {1, 0, 4, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalDrl =
    {1, 0, 5, 1, 1, 0, 0};

/* --- CAN_ID_*_LOCK_* --- */
static const CanSignal_TypeDef kxCanSignalLockDoor =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalLockDisable =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalLockTemp =         /* Locker temp -20.0:50.0 */
    {0.5f, 32, 8, 8, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalLockPlatform =
    {1, 0, 16, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalEngineRun =
    {1, 0, 31, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSSBucketRotate =   /* Skid steer bucket rotation -100.00:100.00 */
    {0.0078125f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalSSBucketHeight =   /* Skid steer bucket height -100.00:100.00 */
    {0.0078125f, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_CONFIG_AXLE --- */
static const CanSignal_TypeDef kxCanSignalSteerConfig =
    {0.004884f, 0, 0, 12, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalSteerTrim =        /* Steering trim */
    {0.0078125f, 0, 0, 16, 1, 1, 0};

/* --- CAN_ID_DATA_AXLE_F (steering feedback) --- */
static const CanSignal_TypeDef kxCanSignalServoEnable =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSteerCurrent =
    {0.0005f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalSteerVoltage =
    {0.003058f, 0, 32, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalSteerTemp =
    {1, 0, 48, 16, 1, 1, 0};

/* --- CAN_ID_CONFIG_MECH_BRAKE_* --- */
static const CanSignal_TypeDef kxCanSignalBrakeConfigNominal =
    {1, 1280, 0, 10, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakeConfigEngage =
    {1, 1280, 10, 10, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakeConfigCustomerMax =
    {1, 1280, 20, 10, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakeConfigEstopSlow =
    {1, 1280, 30, 10, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakeConfigEstopMedium =
    {1, 1280, 40, 10, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBrakeConfigEstopFast =
    {1, 1280, 50, 10, 1, 0, 0};

/* --- CAN_ID_DATA_BATTERY_POWER --- */
static const CanSignal_TypeDef kxCanSignalBatCurrent =       /* Battery current -100.0:100.0 */
    {0.1f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalBatVoltage =       /* Total pack voltage 0.0:100.0 */
    {0.1f, 0, 16, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalCellVoltMax =      /* Max cell voltage 0.0:10.0 */
    {0.01f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalCellVoltMin =      /* Min cell voltage 0.0:10.0 */
    {0.01f, 0, 48, 16, 1, 0, 0};

/* --- CAN_ID_DATA_BATTERY_STATE --- */
static const CanSignal_TypeDef kxCanSignalBatSoc =           /* Battery SOC 0.0:100.0 */
    {0.1f, 0, 0, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalTempMax =          /* Max temperature -100.0:100.0 */
    {0.1f, 0, 16, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalTempMin =          /* Min temperature -100.0:100.0 */
    {0.1f, 0, 32, 16, 1, 1, 0};

/* --- CAN_ID_DIAGNOSE_* --- */
static const CanSignal_TypeDef kxCanSignalResetBoard =
    {1.0f, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalWiFiOff =
    {1.0f, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalBoardTest =
    {1.0f, 0, 2, 1, 1, 0, 0};

/* --- CAN_ID_FAULT_CLEAR --- */
static const CanSignal_TypeDef kxCanSignalFaultClearMotorFr =
    {1.0f, 0, 8, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultClearMotorFl =
    {1.0f, 0, 9, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultClearMotorRr =
    {1.0f, 0, 10, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultClearMotorRl =
    {1.0f, 0, 11, 1, 1, 0, 0};

/* --- CAN_ID_BEAT_* --- */
static const CanSignal_TypeDef kxCanSignalCanTxError =       /* CAN Tx error counter 0:255 */
    {1.0f, 0, 0, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalCanRxError =       /* CAN Rx error counter 0:255 */
    {1.0f, 0, 8, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalErrorData =
    {1.0f, 0, 16, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalUptime =           /* Uptime in seconds */
    {1.0f, 0, 24, 28, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalResetReason =
    {1.0f, 0, 52, 4, 1, 0, 0};

/* --- CAN_ID_SW_VERSION_* --- */
static const CanSignal_TypeDef kxCanSignalSwVersionMajor =
    {1.0f, 0, 0, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSwVersionMinor =
    {1.0f, 0, 16, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSwVersionPatch =
    {1.0f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalSwVersionExperimental =
    {1.0f, 0, 48, 16, 1, 0, 0};

/* --- CAN_ID_FAULT_HIST_MOTOR_* --- */
static const CanSignal_TypeDef kxCanSignalFaultHistMotorFault1 =
    {1.0f, 0, 0, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHistMotorFault2 =
    {1.0f, 0, 16, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHistMotorWarn1 =
    {1.0f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalFaultHistMotorWarn2 =
    {1.0f, 0, 48, 16, 1, 0, 0};

/* --- CAN_ID_CAN_HEALTH_* --- */
static const CanSignal_TypeDef kxCanSignalCanTxErrorMax =
    {1.0f, 0, 0, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalCanRxErrorMax =
    {1.0f, 0, 8, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalCanResetCount =
    {1.0f, 0, 16, 4, 1, 0, 0};

/* --- CAN_ID_FEATURE_ENABLE --- */
static const CanSignal_TypeDef kxCanSignalDisableAntiRollback =
    {1, 0, 0, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalDisableBrakeBlend =
    {1, 0, 1, 1, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalDisableEstopSteering =
    {1, 0, 2, 1, 1, 0, 0};

/* --- CAN_ID_ACTIVE_CAL --- */
static const CanSignal_TypeDef kxCanSignalCalSteerTrim =
    {0.0078125f, 0, 0, 16, 1, 1, 0};
static const CanSignal_TypeDef kxCanSignalHomingComplete =
    {1.0f, 0, 32, 16, 1, 0, 0};

/* --- PDO Position --- */
static const CanSignal_TypeDef kxCanSignalPositionControl =
    {1.0f, 0, 0, 8, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalPositionAddress =
    {1.0f, 0, 8, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalPositionData =
    {1.0f, 0, 16, 16, 1, 0, 0};

/* --- ODrive Set Input Pos --- */
static const CanSignal_TypeDef kxCanSignalInputPos =         /* IEEE 754 float */
    {1, 0, 0, 32, 1, 0, 1};
static const CanSignal_TypeDef kxCanSignalVelFf =
    {0.001f, 0, 32, 16, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalTorqueFf =
    {0.001f, 0, 48, 16, 1, 0, 0};

/* --- ODrive Set Controller Mode --- */
static const CanSignal_TypeDef kxCanSignalControlMode =
    {1, 0, 0, 32, 1, 0, 0};
static const CanSignal_TypeDef kxCanSignalInputMode =
    {1, 0, 32, 32, 1, 0, 0};

/* --- ODrive Set Axis State --- */
static const CanSignal_TypeDef kxCanSignalAxisRequestedState =
    {1, 0, 0, 32, 1, 0, 0};

/******************************************************************************
 * Signal Value Definitions
 *****************************************************************************/

/* PRND Gear values */
#define DRIVE_PRND_PARK      0
#define DRIVE_PRND_REVERSE   1
#define DRIVE_PRND_NEUTRAL   2
#define DRIVE_PRND_DRIVE     3
#define DRIVE_PRND_ESTOP     4

/* Drive modes */
#define DRIVE_MODE_4WD               0
#define DRIVE_MODE_FWD               1
#define DRIVE_MODE_RWD               2
#define DRIVE_MODE_IND_APED          3
#define DRIVE_MODE_KPH               4
#define DRIVE_MODE_RPM               5
#define DRIVE_MODE_ENCODER_ABSOLUTE  6
#define DRIVE_MODE_ENCODER_RELATIVE  7
#define DRIVE_MODE_CURRENT           8

/* Steering modes */
#define STEER_MODE_FWS          0
#define STEER_MODE_RWS          1
#define STEER_MODE_4WS          2
#define STEER_MODE_CRAB         3
#define STEER_MODE_INDEPENDENT  4

/* Mecanum states */
#define MECANUM_STATE_DISABLE   0
#define MECANUM_STATE_ENABLE    1
#define MECANUM_STATE_RESETERR  2
#define MECANUM_STATE_RESETPOS  3
#define MECANUM_STATE_RESETCAL  4
#define MECANUM_STATE_CALSENSOR 5

/* Mecanum modes */
#define MECANUM_MODE_SPEED      0
#define MECANUM_MODE_ABSOLUTE   1
#define MECANUM_MODE_RELATIVE   2
#define MECANUM_MODE_CURRENT    3

/* Locker door states */
#define LOCKER_DOOR_CLOSED   0
#define LOCKER_DOOR_OPENED   1
#define LOCKER_DOOR_CLOSING  2
#define LOCKER_DOOR_OPENING  3

#ifdef __cplusplus
}
#endif

#endif /* __CAN_MESSAGES_H */
