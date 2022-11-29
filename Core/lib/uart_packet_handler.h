/*
 * uart_packect_helper.h
 *
 *  Created on: Aug 10, 2020
 *      Author: mengjingshi
 */

#ifndef UART_PACKECT_HELPER_H_
#define UART_PACKECT_HELPER_H_

#include "uart_comm_helper.h"

typedef struct
{
	void *priv;
	LinkLayerHandler llhandler;
} UartMessageHandler;


void UartPacketHandlerInit(UartMessageHandler *msgHandler, UART_HandleTypeDef *uart, DMA_HandleTypeDef *dma);

void UartPacketSetFunction(UartMessageHandler *msgHandler, PacketArrived pHandlerPacket);


#endif /* UART_PACKECT_HELPER_H_ */
