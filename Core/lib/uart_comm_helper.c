/*
 * uart_comm_helper.c
 *
 *  Created on: Jul 25, 2020
 *      Author: mengjingshi
 */
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "uart_comm_helper.h"

#define FALSE 0
#define TRUE 1

static void delay_us(uint32_t u_sec) {
  uint16_t cnt = 0;

  while (u_sec--) {
    for (cnt = 168 / 5; cnt > 0; cnt--)
      ;
  }
}

//延时nms
//nms:要延时的ms数
static void delay_ms(uint16_t nms) {
  uint32_t i;
  for (i = 0; i < nms; i++)
    delay_us(1000);
}


void UART_IDLE_Callback(LinkLayerHandler *self, UART_HandleTypeDef *huart) {
  uint8_t tmp1 = 0, tmp2 = 0;
  uint16_t len1 = 0, len2 = 0;
  tmp1 = __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE);
  tmp2 = __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE);
  __HAL_UART_CLEAR_IDLEFLAG(huart);
  len1 = RECV_BUF_MAX - __HAL_DMA_GET_COUNTER(self->dma_rx);
  delay_ms(50);
  len2 = RECV_BUF_MAX - __HAL_DMA_GET_COUNTER(self->dma_rx);
  if (len1 != len2) {
    return;
  }
  if ((tmp1 != RESET) && (tmp2 != RESET)) {
    self->FrameLength = RECV_BUF_MAX - __HAL_DMA_GET_COUNTER(self->dma_rx);
  }
  self->deliver_packet(self->m_framePayload, self->FrameLength, self->arg);
  HAL_UART_DMAResume(huart);
  __HAL_DMA_DISABLE(self->dma_rx);
  memset(self->m_framePayload, 0, self->FrameLength);
  self->dma_rx->Instance->NDTR = RECV_BUF_MAX;
  __HAL_DMA_ENABLE(self->dma_rx);
}

void LLInit(LinkLayerHandler *self, UART_HandleTypeDef *uart, DMA_HandleTypeDef *dma_rx) {
  self->uart = uart;
  self->dma_rx = dma_rx;
  __HAL_UART_ENABLE_IT(self->uart, UART_IT_IDLE);
  HAL_UART_Receive_DMA(self->uart, self->m_framePayload, RECV_BUF_MAX);
}

#if USE_FREERTOS
extern volatile int memoryLockOpen;
#endif
void LLSendData(LinkLayerHandler *self, uint8_t *data, size_t len) {
#if USE_FREERTOS
	if(memoryLockOpen){
                vTaskSuspendAll();
        }
#endif
  HAL_UART_Transmit(self->uart, (uint8_t*) data, (uint16_t) len, 0xfffff);
#if USE_FREERTOS
  if(memoryLockOpen){
                xTaskResumeAll();
        }
#endif
}

