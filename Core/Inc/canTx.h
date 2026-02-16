/**
 ******************************************************************************
 * @file           : canTx.h
 * @brief          : CAN transmit helper with mailbox-full retry
 ******************************************************************************
 */

#ifndef __CAN_TX_H
#define __CAN_TX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Defines -------------------------------------------------------------------*/
#define CAN_TX_MAX_RETRIES 5
#define CAN_TX_RETRY_DELAY_MS 1

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Transmit a CAN frame with retry on mailbox full.
 *
 *         Checks for a free TX mailbox before sending. If all 3 mailboxes
 *         are occupied, waits CAN_TX_RETRY_DELAY_MS and retries up to
 *         CAN_TX_MAX_RETRIES times. Must be called from a FreeRTOS task
 *         context (uses osDelay).
 *
 * @param  hcan     Pointer to CAN handle
 * @param  pHeader  Pointer to TX header
 * @param  pData    Pointer to data buffer (up to 8 bytes)
 * @retval HAL_OK on success, HAL_BUSY if all retries exhausted,
 *         HAL_ERROR on HAL driver error
 */
HAL_StatusTypeDef CAN_TransmitRetry(CAN_HandleTypeDef *hcan,
                                    CAN_TxHeaderTypeDef *pHeader,
                                    uint8_t *pData);

#ifdef __cplusplus
}
#endif

#endif /* __CAN_TX_H */
