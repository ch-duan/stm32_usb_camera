/*
 * uart_comm_helper.h
 *
 *  Created on: Aug 10, 2020
 *      Author: mengjingshi
 */

#ifndef UART_COMM_HELPER_H_
#define UART_COMM_HELPER_H_

#include "stm32f4xx_hal.h"
//dma receive buf queue
#define RECV_BUF_MAX 5120
#define USE_FREERTOS 0
typedef void (*PacketArrived)(uint8_t *packet, uint16_t packetLen, void *arg);

typedef struct {
  UART_HandleTypeDef *uart;
  DMA_HandleTypeDef *dma_rx;

  PacketArrived deliver_packet;
  void *arg;

  uint16_t FrameLength;
  uint8_t m_framePayload[RECV_BUF_MAX];
} LinkLayerHandler;

void LLInit(LinkLayerHandler *self, UART_HandleTypeDef *uart, DMA_HandleTypeDef *dma_rx);
void LLSendData(LinkLayerHandler *self, uint8_t *data, size_t len);
void UART_IDLE_Callback(LinkLayerHandler *self, UART_HandleTypeDef *huart);
#endif /* UART_COMM_HELPER_H_ */
