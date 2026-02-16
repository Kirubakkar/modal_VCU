/**
  ******************************************************************************
  * @file           : vcu.h
  * @brief          : VCU application header
  ******************************************************************************
  */

#ifndef __VCU_H
#define __VCU_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported functions prototypes ---------------------------------------------*/
void initVCU(void);
void initTelems(void);
void VCU_ProcessRxMessage(uint32_t stdId, uint8_t *data, uint8_t dlc);

#ifdef __cplusplus
}
#endif

#endif /* __VCU_H */
