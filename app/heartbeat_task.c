/*
 * heartbeat_task.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include "heartbeat_task.h"

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

/* Heartbeat task function */
static void HeartbeatTask(void *pvParameters)
{
    (void) pvParameters;

    while (1)
    {
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, GPIO_PIN_1);
        vTaskDelay(pdMS_TO_TICKS(500));

        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1, 0);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

/* Task creation function */
void HeartbeatTask_Init(void)
{
    xTaskCreate(
        HeartbeatTask,
        "Heartbeat",
        128,
        NULL,
        tskIDLE_PRIORITY + 1,
        NULL
    );
}

