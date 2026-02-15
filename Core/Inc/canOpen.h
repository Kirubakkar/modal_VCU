/**
 ******************************************************************************
 * @file           : canOpen.h
 * @brief          : CANopen SDO client header
 ******************************************************************************
 */

#ifndef __CANOPEN_H
#define __CANOPEN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdint.h>

/* SDO Command Specifiers ----------------------------------------------------*/
/* Client -> Server (TX) command bytes for Expedited Download (write) */
#define SDO_CCS_DOWNLOAD_INITIATE 0x01 /* Initiate Download Request */

/* SDO command byte building:
 *   Bits 7-5: ccs (client command specifier) = 001 for download initiate
 *   Bit 4:    reserved (0)
 *   Bits 3-2: n  (number of bytes in data that do NOT contain data)
 *   Bit 1:    e  (1 = expedited transfer)
 *   Bit 0:    s  (1 = size indicated)
 */
#define SDO_EXPEDITED_1BYTE 0x2F /* ccs=1, n=3, e=1, s=1 -> 1 data byte  */
#define SDO_EXPEDITED_2BYTE 0x2B /* ccs=1, n=2, e=1, s=1 -> 2 data bytes */
#define SDO_EXPEDITED_3BYTE 0x27 /* ccs=1, n=1, e=1, s=1 -> 3 data bytes */
#define SDO_EXPEDITED_4BYTE 0x23 /* ccs=1, n=0, e=1, s=1 -> 4 data bytes */

/* Server -> Client (RX) response command bytes */
#define SDO_SCS_DOWNLOAD_INITIATE                                              \
  0x60                         /* Download Initiate Response (success) */
#define SDO_ABORT_COMMAND 0x80 /* Abort Transfer */

/* CANopen COB-ID definitions ------------------------------------------------*/
#define SDO_TX_COB_ID_BASE 0x600 /* Client->Server: 0x600 + Node-ID */
#define SDO_RX_COB_ID_BASE 0x580 /* Server->Client: 0x580 + Node-ID */

/* Timeout -------------------------------------------------------------------*/
#define SDO_TIMEOUT_MS 1000 /* SDO response timeout in milliseconds */

/* Return codes --------------------------------------------------------------*/
typedef enum {
  SDO_OK = 0x00,
  SDO_ERR_TIMEOUT = 0x01,
  SDO_ERR_ABORT = 0x02,
  SDO_ERR_TX_FAIL = 0x03,
  SDO_ERR_PARAM = 0x04,
} SDO_Status_t;

/* Function prototypes -------------------------------------------------------*/

/**
 * @brief  Perform a CANopen SDO expedited write (download) to a remote node.
 * @param  hcan      Pointer to CAN handle (e.g. &hcan1)
 * @param  nodeId    Target CANopen node ID (1-127)
 * @param  index     Object Dictionary index (16-bit)
 * @param  subIndex  Object Dictionary sub-index (8-bit)
 * @param  data      Pointer to data to write
 * @param  dataLen   Number of data bytes to write (1-4 for expedited transfer)
 * @retval SDO_Status_t  SDO_OK on success, error code otherwise
 */
SDO_Status_t SDO_Write(CAN_HandleTypeDef *hcan, uint8_t nodeId, uint16_t index,
                       uint8_t subIndex, uint8_t dataLen, uint8_t *data);

#ifdef __cplusplus
}
#endif

#endif /* __CANOPEN_H */
