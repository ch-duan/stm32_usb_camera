/*
 * uart_packet_handler.c
 *
 *  Created on: Aug 10, 2020
 *      Author: mengjingshi
 */
#include "uart_packet_handler.h"

void UartPacketHandlerInit(UartMessageHandler *msgHandler, UART_HandleTypeDef *uart, DMA_HandleTypeDef *dma) {
	msgHandler->priv = NULL;
	msgHandler->llhandler.arg = msgHandler;
  LLInit(&(msgHandler->llhandler), uart, dma);
}

void UartPacketSetFunction(UartMessageHandler *msgHandler, PacketArrived pHandlerPacket) {
	msgHandler->llhandler.deliver_packet = pHandlerPacket;
}

