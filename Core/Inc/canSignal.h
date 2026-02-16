/**
 ******************************************************************************
 * @file           : canSignal.h
 * @brief          : CAN signal packing and extraction
 ******************************************************************************
 */

#ifndef __CAN_SIGNAL_H
#define __CAN_SIGNAL_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Constants -----------------------------------------------------------------*/
#define NUM_BITS_PER_BYTE 8

/* Typedefs ------------------------------------------------------------------*/
typedef struct {
  float f_scaler;        /* Scaler */
  float f_offset;        /* Offset */
  uint8_t uc_start;      /* Start bit */
  uint8_t uc_length;     /* Length in bits */
  uint8_t uc_little_end; /* Endianness: 1 = little endian, 0 = big endian */
  uint8_t uc_signed;     /* Signed: 1 = signed, 0 = unsigned */
  uint8_t b_float;       /* IEEE 754 float: 1 = yes, 0 = no */
} CanSignal_TypeDef;

/* Exported functions --------------------------------------------------------*/
float canExtract(uint8_t *puc_data, const CanSignal_TypeDef *signal);
void canPack(uint8_t *puc_data, const CanSignal_TypeDef *signal, float f_value);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_SIGNAL_H */
