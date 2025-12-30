/*
 * uart_drv.h
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#ifndef DRIVERS_UART_DRV_H_
#define DRIVERS_UART_DRV_H_

#include <stdint.h>
#include "FreeRTOS.h"
#include "queue.h"

void UART0_Init(uint32_t baudrate);
void UART0_SendChar(char c);
void UART0_SendString(const char *str);

extern QueueHandle_t uartRxQueue;

#endif /* DRIVERS_UART_DRV_H_ */
