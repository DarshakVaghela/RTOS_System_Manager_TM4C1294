/*
 * button_task.c
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#include "button_task.h"

#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "inc/hw_ints.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"

static TaskHandle_t buttonTaskHandle = NULL;

/* Button Task */
static void ButtonTask(void *pvParameters)
{
    (void)pvParameters;

    while (1)
    {
        /* Wait indefinitely for button interrupt */
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);

        /* Toggle PN1 LED */
        GPIOPinWrite(GPIO_PORTN_BASE, GPIO_PIN_1,
                     GPIOPinRead(GPIO_PORTN_BASE, GPIO_PIN_1) ^ GPIO_PIN_1);
    }
}

/* GPIO Interrupt Handler for Port J */
void GPIOJ_Handler(void)
{
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    GPIOIntClear(GPIO_PORTJ_BASE, GPIO_PIN_0);

    xTaskNotifyFromISR(
        buttonTaskHandle,
        0,
        eNoAction,
        &xHigherPriorityTaskWoken
    );

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
}

/* Button Task Init */
void ButtonTask_Init(void)
{
    /* Enable GPIO Port J */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOJ);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOJ));

    /* Unlock PJ0 */
    HWREG(GPIO_PORTJ_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
    HWREG(GPIO_PORTJ_BASE + GPIO_O_CR) |= GPIO_PIN_0;
    HWREG(GPIO_PORTJ_BASE + GPIO_O_LOCK) = 0;

    GPIOPinTypeGPIOInput(GPIO_PORTJ_BASE, GPIO_PIN_0);
    GPIOPadConfigSet(GPIO_PORTJ_BASE, GPIO_PIN_0,
                     GPIO_STRENGTH_2MA, GPIO_PIN_TYPE_STD_WPU);

    GPIOIntTypeSet(GPIO_PORTJ_BASE, GPIO_PIN_0, GPIO_FALLING_EDGE);
    GPIOIntEnable(GPIO_PORTJ_BASE, GPIO_PIN_0);

    IntEnable(INT_GPIOJ);

    xTaskCreate(
        ButtonTask,
        "Button",
        128,
        NULL,
        tskIDLE_PRIORITY + 2,
        &buttonTaskHandle
    );
}

