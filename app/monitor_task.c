/*
 * monitor_task.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include "monitor_task.h"
#include "uart_drv.h"

#include "FreeRTOS.h"
#include "task.h"

#include <stdio.h>

static void MonitorTask(void *pvParameters)
{
    char buffer[256];

    (void)pvParameters;

    while (1)
    {
        vTaskList(buffer);
        UART0_SendString("\r\nTask List:\r\n");
        UART0_SendString("Name          State   Prio   Stack   Num\r\n");
        UART0_SendString(buffer);

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void MonitorTask_Init(void)
{
    xTaskCreate(
        MonitorTask,
        "Monitor",
        256,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}

