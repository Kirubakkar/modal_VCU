/**
 ******************************************************************************
 * @file           : canSignal.c
 * @brief          : CAN signal packing and extraction
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "canSignal.h"
#include <string.h>

/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Returns a bit mask for a single byte of a CAN payload
 * @param  uc_byte_num   Array byte number to make a mask for
 * @param  uc_bit_sig_lsb  Least significant bit for the signal
 * @param  uc_bit_sig_msb  Most significant bit for the signal
 * @retval Bit mask for the byte
 */
static uint8_t ucGetByteBitMask(uint8_t uc_byte_num, uint8_t uc_bit_sig_lsb,
                                uint8_t uc_bit_sig_msb) {
  uint8_t uc_bit_mask_lsb = 0;
  uint8_t uc_bit_mask_msb = 0;
  int32_t l_bit_byte_lsb = 0;
  int32_t l_bit_byte_msb = 0;

  l_bit_byte_lsb = uc_byte_num * NUM_BITS_PER_BYTE;
  l_bit_byte_msb = (uc_byte_num + 1) * NUM_BITS_PER_BYTE - 1;

  uc_bit_mask_lsb = (uint8_t)(uc_bit_sig_lsb < l_bit_byte_lsb
                                   ? 0
                                   : uc_bit_sig_lsb - l_bit_byte_lsb);
  uc_bit_mask_msb = (uint8_t)(uc_bit_sig_msb >= l_bit_byte_msb
                                   ? NUM_BITS_PER_BYTE - 1
                                   : uc_bit_sig_msb - l_bit_byte_lsb);

  return (uint8_t)((UINT8_MAX << (uc_bit_mask_msb + 1)) ^
                   (UINT8_MAX << uc_bit_mask_lsb));
}

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Extracts a CAN signal from data buffer
 *
 *         Currently limited to 32-bit signals.
 *         Caller to cast the result to an alternate data type if needed.
 *
 * @param  puc_data  CAN data array (8 bytes)
 * @param  signal    Signal configuration
 * @retval Extracted signal value (scaled and offset applied)
 */
float canExtract(uint8_t *puc_data, const CanSignal_TypeDef *signal) {
  uint32_t ul_ret = 0;
  float f_ret = 0.0f;
  uint8_t uc_byte_shift = 0;

  uint8_t uc_bit_sig_lsb = signal->uc_start;
  uint8_t uc_bit_sig_msb = (uint8_t)(uc_bit_sig_lsb + signal->uc_length - 1);
  uint8_t uc_byte_start = uc_bit_sig_lsb / NUM_BITS_PER_BYTE;
  uint8_t uc_byte_stop = uc_bit_sig_msb / NUM_BITS_PER_BYTE;

  for (uint8_t i = uc_byte_start; i <= uc_byte_stop; i++) {
    if (signal->uc_little_end) {
      uc_byte_shift = (uint8_t)(i - uc_byte_start);
    } else {
      uc_byte_shift = (uint8_t)(uc_byte_stop - i);
    }

    ul_ret += (uint32_t)((ucGetByteBitMask(i, uc_bit_sig_lsb, uc_bit_sig_msb) &
                           puc_data[i])
                          << uc_byte_shift * NUM_BITS_PER_BYTE);
  }

  ul_ret >>= uc_bit_sig_lsb - NUM_BITS_PER_BYTE * uc_byte_start;

  if (!signal->b_float) {
    if (signal->uc_signed) {
      if ((int32_t)ul_ret &
          (1 << (uc_bit_sig_msb - uc_byte_start * NUM_BITS_PER_BYTE))) {
        ul_ret |= (uint32_t)(~(uint64_t)0
                              << (uc_bit_sig_msb -
                                  uc_byte_start * NUM_BITS_PER_BYTE + 1));
      }
      f_ret = (float)(int32_t)ul_ret;
    } else {
      f_ret = (float)ul_ret;
    }
  } else {
    memcpy(&f_ret, &ul_ret, sizeof(f_ret));
  }

  return f_ret * signal->f_scaler + signal->f_offset;
}

/**
 * @brief  Packs a CAN signal into a data buffer
 *
 *         Currently limited to 32-bit signals.
 *         Note that precision loss may occur due to the use of floats.
 *
 * @param  puc_data  CAN data array (8 bytes)
 * @param  signal    Signal configuration
 * @param  f_value   Signal value to pack
 */
void canPack(uint8_t *puc_data, const CanSignal_TypeDef *signal,
             float f_value) {
  uint8_t uc_bit_mask = 0;
  uint32_t ul_byte_value = 0;

  uint8_t uc_bit_sig_lsb = signal->uc_start;
  uint8_t uc_bit_sig_msb =
      (uint8_t)(uc_bit_sig_lsb + signal->uc_length - 1);
  uint8_t uc_bit_sig_adjust = uc_bit_sig_lsb % NUM_BITS_PER_BYTE;

  uint8_t uc_byte_start = uc_bit_sig_lsb / NUM_BITS_PER_BYTE;
  uint8_t uc_byte_stop = uc_bit_sig_msb / NUM_BITS_PER_BYTE;

  uint32_t ul_pack_value = 0;

  if (!signal->b_float) {
    ul_pack_value =
        (uint32_t)(int32_t)((f_value - signal->f_offset) / signal->f_scaler);
  } else {
    memcpy(&ul_pack_value, &f_value, sizeof(ul_pack_value));
  }

  for (uint8_t i = uc_byte_start; i <= uc_byte_stop; i++) {
    uc_bit_mask = ucGetByteBitMask(i, uc_bit_sig_lsb, uc_bit_sig_msb);
    puc_data[i] &= (uint8_t)(~uc_bit_mask);

    if (i == uc_byte_start) {
      ul_byte_value = ul_pack_value << uc_bit_sig_adjust;
    } else {
      ul_byte_value = ul_pack_value >>
                      ((i - uc_byte_start) * NUM_BITS_PER_BYTE -
                       uc_bit_sig_adjust);
    }
    puc_data[i] |= (uint8_t)((uc_bit_mask & ul_byte_value) & 0xFF);
  }
}
