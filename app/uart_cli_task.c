/*
 * uart_cli_task.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include "uart_cli_task.h"
#include "uart_drv.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include <string.h>

//static SemaphoreHandle_t uartMutex;

static void UART_CLITask(void *pvParameters)
{
    char ch;
    char cmdBuffer[32];
    uint8_t idx = 0;

    UART0_SendString("\r\nRTOS CLI Ready\r\n> ");

    while (1)
    {
        if (xQueueReceive(uartRxQueue, &ch, portMAX_DELAY) == pdTRUE)
        {
            UART0_SendChar(ch);  // echo

            if (ch == '\r' || ch == '\n')
            {
                cmdBuffer[idx] = '\0';

                if (strcmp(cmdBuffer, "status") == 0)
                {
                    UART0_SendString("\r\nSystem OK\r\n");
                }
                else if (strcmp(cmdBuffer, "tasks") == 0)
                {
                    UART0_SendString("\r\nUse monitor output\r\n");
                }
                else
                {
                    UART0_SendString("\r\nUnknown command\r\n");
                }

                idx = 0;
                UART0_SendString("> ");
            }
            else if (idx < sizeof(cmdBuffer) - 1)
            {
                cmdBuffer[idx++] = ch;
            }
        }
    }
}

void UART_CLI_TaskInit(void)
{
    //uartMutex = xSemaphoreCreateMutex();

    xTaskCreate(
        UART_CLITask,
        "UART_CLI",
        256,
        NULL,
        tskIDLE_PRIORITY + 2,
        NULL
    );
}

