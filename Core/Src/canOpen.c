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
static osSemaphoreId_t sdoRxSemaphore = NULL;
static volatile uint8_t sdoRxResponseData[8] = {0};
static volatile uint32_t sdoRxExpectedCobId = 0;
static volatile uint8_t sdoRxReceived = 0;

/* Private function prototypes -----------------------------------------------*/

/* Exported functions --------------------------------------------------------*/

/**
 * @brief  Initialize CANopen SDO layer.
 */
void SDO_Init(void) {
  sdoRxSemaphore = osSemaphoreNew(1, 0, NULL);
}

/**
 * @brief  Process a received CAN frame for SDO responses.
 *         Call this from the CAN RX ISR callback.
 */
void SDO_ProcessRxMessage(uint32_t stdId, uint8_t *data, uint8_t dlc) {
  /* Check if this is the SDO response we're waiting for */
  if (stdId == sdoRxExpectedCobId && sdoRxReceived == 0) {
    memcpy((void *)sdoRxResponseData, data, 8);
    sdoRxReceived = 1;
    if (sdoRxSemaphore != NULL) {
      osSemaphoreRelease(sdoRxSemaphore);
    }
  }
}

/**
 * @brief  Perform a CANopen SDO expedited write (download) to a remote node.
 */
SDO_Status_t SDO_Write(CAN_HandleTypeDef *hcan, uint8_t nodeId, uint16_t index,
                       uint8_t subIndex, uint8_t dataLen, float scalar,
                       uint8_t *data) {
  /* --- Parameter validation --- */
  if (hcan == NULL || data == NULL)
    return SDO_ERR_PARAM;
  if (nodeId == 0 || nodeId > 127)
    return SDO_ERR_PARAM;
  if (dataLen == 0 || dataLen > 4)
    return SDO_ERR_PARAM;
  if (sdoRxSemaphore == NULL)
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

  /* --- Apply scalar to data --- */
  int32_t rawValue = 0;
  for (uint8_t i = 0; i < dataLen; i++) {
    rawValue |= ((int32_t)data[i]) << (i * 8);
  }
  int32_t scaledValue = (int32_t)((float)rawValue * scalar);

  /* --- Build the 8-byte SDO TX payload --- */
  uint8_t txPayload[8] = {0};
  txPayload[0] = commandByte;
  txPayload[1] = (uint8_t)(index & 0xFF);        /* Index low byte  */
  txPayload[2] = (uint8_t)((index >> 8) & 0xFF); /* Index high byte */
  txPayload[3] = subIndex;

  /* Copy scaled data into bytes 4-7 (little-endian, remaining bytes stay 0) */
  for (uint8_t i = 0; i < dataLen; i++) {
    txPayload[4 + i] = (uint8_t)((scaledValue >> (i * 8)) & 0xFF);
  }

  /* --- Configure CAN TX header --- */
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = SDO_TX_COB_ID_BASE + nodeId; /* 0x600 + Node-ID */
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 8; /* SDO frames are always 8 bytes */
  txHeader.TransmitGlobalTime = DISABLE;

  /* --- Retry loop: up to SDO_WRITE_RETRIES attempts --- */
  for (uint8_t attempt = 0; attempt < SDO_WRITE_RETRIES; attempt++) {
    /* Prepare to receive confirmation */
    sdoRxExpectedCobId = SDO_RX_COB_ID_BASE + nodeId; /* 0x580 + Node-ID */
    sdoRxReceived = 0;

    /* Drain any stale semaphore tokens */
    while (osSemaphoreAcquire(sdoRxSemaphore, 0) == osOK) {}

    /* Transmit */
    uint32_t txMailbox;
    if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0)
      return SDO_ERR_TX_FAIL;

    if (HAL_CAN_AddTxMessage(hcan, &txHeader, txPayload, &txMailbox) != HAL_OK)
      return SDO_ERR_TX_FAIL;

    /* Wait for server confirmation (0x60) or abort (0x80) */
    osStatus_t semStatus = osSemaphoreAcquire(sdoRxSemaphore, SDO_TIMEOUT_MS);
    if (semStatus != osOK)
      continue; /* Timeout - retry */

    /* Check response */
    uint8_t cmdByte = sdoRxResponseData[0];

    /* Abort? */
    if ((cmdByte & 0x80) == 0x80)
      return SDO_ERR_ABORT;

    /* Success (0x60 = Download Initiate Response) */
    return SDO_OK;
  }

  /* All retries exhausted */
  return SDO_ERR_TIMEOUT;
}

/**
 * @brief  Perform a CANopen SDO expedited read (upload) from a remote node.
 *
 *         SDO Upload Initiate Request (8 bytes):
 *         Byte 0:   0x40 (Upload Initiate, ccs=2)
 *         Byte 1-2: Index (little-endian)
 *         Byte 3:   Sub-index
 *         Byte 4-7: Reserved (0x00)
 *
 *         Waits for server response on 0x580 + nodeId using a semaphore.
 */
SDO_Status_t SDO_Read(CAN_HandleTypeDef *hcan, uint8_t nodeId, uint16_t index,
                      uint8_t subIndex, uint8_t dataLen, float scalar,
                      uint8_t *data) {
  (void)scalar; /* scalar is unused for read — present for macro compatibility */
  /* --- Parameter validation --- */
  if (hcan == NULL || data == NULL)
    return SDO_ERR_PARAM;
  if (nodeId == 0 || nodeId > 127)
    return SDO_ERR_PARAM;
  if (dataLen == 0 || dataLen > 4)
    return SDO_ERR_PARAM;
  if (sdoRxSemaphore == NULL)
    return SDO_ERR_PARAM;

  /* --- Build the 8-byte SDO Upload Initiate request --- */
  uint8_t txPayload[8] = {0};
  txPayload[0] = SDO_CCS_UPLOAD_INITIATE; /* 0x40 */
  txPayload[1] = (uint8_t)(index & 0xFF);
  txPayload[2] = (uint8_t)((index >> 8) & 0xFF);
  txPayload[3] = subIndex;

  /* --- Configure CAN TX header --- */
  CAN_TxHeaderTypeDef txHeader;
  txHeader.StdId = SDO_TX_COB_ID_BASE + nodeId;
  txHeader.ExtId = 0;
  txHeader.IDE = CAN_ID_STD;
  txHeader.RTR = CAN_RTR_DATA;
  txHeader.DLC = 8;
  txHeader.TransmitGlobalTime = DISABLE;

  /* --- Retry loop: up to SDO_READ_RETRIES attempts --- */
  for (uint8_t attempt = 0; attempt < SDO_READ_RETRIES; attempt++) {
    /* Prepare to receive */
    sdoRxExpectedCobId = SDO_RX_COB_ID_BASE + nodeId; /* 0x580 + Node-ID */
    sdoRxReceived = 0;

    /* Drain any stale semaphore tokens */
    while (osSemaphoreAcquire(sdoRxSemaphore, 0) == osOK) {}

    /* Transmit */
    uint32_t txMailbox;
    if (HAL_CAN_GetTxMailboxesFreeLevel(hcan) == 0)
      return SDO_ERR_TX_FAIL;

    if (HAL_CAN_AddTxMessage(hcan, &txHeader, txPayload, &txMailbox) != HAL_OK)
      return SDO_ERR_TX_FAIL;

    /* Wait for response with timeout */
    osStatus_t semStatus = osSemaphoreAcquire(sdoRxSemaphore, SDO_TIMEOUT_MS);
    if (semStatus != osOK)
      continue; /* Timeout - retry */

    /* Check response */
    uint8_t cmdByte = sdoRxResponseData[0];

    /* Abort? */
    if ((cmdByte & 0x80) == 0x80)
      return SDO_ERR_ABORT;

    /* Copy data bytes 4-7 from response */
    for (uint8_t i = 0; i < dataLen; i++) {
      data[i] = sdoRxResponseData[4 + i];
    }

    return SDO_OK;
  }

  /* All retries exhausted */
  return SDO_ERR_TIMEOUT;
}
