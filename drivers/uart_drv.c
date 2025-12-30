/*
 * uart_drv.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include <stdint.h>
#include <stdbool.h>

#include "uart_drv.h"

#include "inc/hw_memmap.h"
#include "inc/hw_ints.h"

#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"

QueueHandle_t uartRxQueue = NULL;

void UART0_Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    uint32_t status;
    char ch;

    status = UARTIntStatus(UART0_BASE, true);
    UARTIntClear(UART0_BASE, status);

    while (UARTCharsAvail(UART0_BASE))
    {
        ch = UARTCharGetNonBlocking(UART0_BASE);
        xQueueSendFromISR(uartRxQueue, &ch, &xHigherPriorityTaskWoken);
    }

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

void UART0_Init(uint32_t baudrate)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTConfigSetExpClk(
        UART0_BASE,
        SysCtlClockGet(),
        baudrate,
        (UART_CONFIG_WLEN_8 |
         UART_CONFIG_STOP_ONE |
         UART_CONFIG_PAR_NONE)
    );

    uartRxQueue = xQueueCreate(64, sizeof(char));

    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    IntEnable(INT_UART0);
    UARTEnable(UART0_BASE);
}

void UART0_SendChar(char c)
{
    UARTCharPut(UART0_BASE, c);
}

void UART0_SendString(const char *str)
{
    while (*str)
    {
        UART0_SendChar(*str++);
    }
}

