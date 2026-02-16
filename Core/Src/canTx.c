/**
 ******************************************************************************
 * @file           : canTx.c
 * @brief          : CAN transmit helper with mailbox-full retry
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "canTx.h"
#include "cmsis_os.h"

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Transmit a CAN frame with retry on mailbox full.
 */
HAL_StatusTypeDef CAN_TransmitRetry(CAN_HandleTypeDef *hcan,
                                    CAN_TxHeaderTypeDef *pHeader,
                                    uint8_t *pData) {
  uint32_t txMailbox;

  for (uint8_t attempt = 0; attempt < CAN_TX_MAX_RETRIES; attempt++) {
    if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) > 0) {
      HAL_StatusTypeDef status =
          HAL_CAN_AddTxMessage(hcan, pHeader, pData, &txMailbox);
      if (status == HAL_OK) {
        return HAL_OK;
      }
      /* HAL_ERROR — peripheral issue, no point retrying */
      return HAL_ERROR;
    }

    /* All mailboxes occupied — wait and retry */
    osDelay(CAN_TX_RETRY_DELAY_MS);
  }

  /* All retries exhausted, mailboxes still full */
  return HAL_BUSY;
}
