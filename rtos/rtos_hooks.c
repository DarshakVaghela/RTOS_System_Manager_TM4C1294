/*
 * rtos_hooks.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include "rtos_hooks.h"

#include "FreeRTOS.h"
#include "task.h"

/* Called if pvPortMalloc() fails */
void vApplicationMallocFailedHook(void)
{
    taskDISABLE_INTERRUPTS();
    while (1)
    {
        /* Trap here for debugging */
    }
}

/* Called if a stack overflow is detected */
void vApplicationStackOverflowHook(void *xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;

    taskDISABLE_INTERRUPTS();
    while (1)
    {
        /* Trap here for debugging */
    }
}

/* Called when configASSERT() fails */
void vAssertCalled(const char *pcFile, int32_t ulLine)
{
    (void)pcFile;
    (void)ulLine;

    taskDISABLE_INTERRUPTS();
    while (1)
    {
        /* Trap here for debugging */
    }
}

