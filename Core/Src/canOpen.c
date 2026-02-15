/**
 ******************************************************************************
 * @file           : canOpen.c
 * @brief          : CANopen SDO client implementation
 ******************************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "canOpen.h"
#include "cmsis_os.h"
#include <string.h>

/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Perform a CANopen SDO expedited write (download) to a remote node.
 *
 *         Sends an SDO Download Initiate request and waits for the server
 *         response (confirmation or abort).
 *
 *         CANopen SDO Write frame (8 bytes):
 *         Byte 0:   Command specifier (depends on data length)
 *         Byte 1-2: Index (little-endian)
 *         Byte 3:   Sub-index
 *         Byte 4-7: Data (little-endian, zero-padded)
 *
 * @param  hcan      Pointer to CAN handle (e.g. &hcan1)
 * @param  nodeId    Target CANopen node ID (1-127)
 * @param  index     Object Dictionary index (16-bit)
 * @param  subIndex  Object Dictionary sub-index (8-bit)
 * @param  data      Pointer to data bytes to write
 * @param  dataLen   Number of data bytes (1-4 for expedited transfer)
 * @retval SDO_Status_t  SDO_OK on success, error code otherwise
 */
SDO_Status_t SDO_Write(CAN_HandleTypeDef *hcan, uint8_t nodeId, uint16_t index,
                       uint8_t subIndex, uint8_t dataLen, uint8_t *data) {
  /* --- Parameter validation --- */
  if (hcan == NULL || data == NULL)
    return SDO_ERR_PARAM;
  if (nodeId == 0 || nodeId > 127)
    return SDO_ERR_PARAM;
  if (dataLen == 0 || dataLen > 4)
    return SDO_ERR_PARAM;

  /* --- Build the SDO command byte --- */
  uint8_t commandByte;
  switch (dataLen) {
  case 1:
    commandByte = SDO_EXPEDITED_1BYTE;
    break;
  case 2:
    commandByte = SDO_EXPEDITED_2BYTE;
    break;
  case 3:
    commandByte = SDO_EXPEDITED_3BYTE;
    break;
  case 4:
    commandByte = SDO_EXPEDITED_4BYTE;
    break;
  default:
    return SDO_ERR_PARAM;
  }

  /* --- Build the 8-byte SDO TX payload --- */
  uint8_t txPayload[8] = {0};
  txPayload[0] = commandByte;
  txPayload[1] = (uint8_t)(index & 0xFF);        /* Index low byte  */
  txPayload[2] = (uint8_t)((index >> 8) & 0xFF); /* Index high byte */
  txPayload[3] = subIndex;

  /* Copy data into bytes 4-7 (little-endian, remaining bytes stay 0) */
  for (uint8_t i = 0; i < dataLen; i++) {
    txPayload[4 + i] = data[i];
  }

  /* --- Configure CAN TX header --- */
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = SDO_TX_COB_ID_BASE + nodeId; /* 0x600 + Node-ID */
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 8; /* SDO frames are always 8 bytes */
  txHeader.TransmitGlobalTime = DISABLE;

  /* --- Transmit the SDO request --- */
  uint32_t txMailbox;
  if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0)
    return SDO_ERR_TX_FAIL;

  if (HAL_CAN_AddTxMessage(hcan, &txHeader, txPayload, &txMailbox) != HAL_OK)
    return SDO_ERR_TX_FAIL;

  /* --- Wait for SDO response from server (0x580 + Node-ID) --- */
  /* TODO: Implement RX polling or callback-based response handling.
   *       For now, this function only transmits the SDO request.
   *       You can add response waiting logic here later, e.g.:
   *       - Poll HAL_CAN_GetRxMessage() with a timeout
   *       - Or use RX FIFO interrupt + a FreeRTOS queue/semaphore
   */

  return SDO_OK;
}
