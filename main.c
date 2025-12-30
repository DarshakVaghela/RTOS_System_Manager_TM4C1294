#include <stdint.h>
#include <stdbool.h>

#include "inc/hw_memmap.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

#include "FreeRTOS.h"
#include "task.h"

#include "heartbeat_task.h"
#include "button_task.h"

#include "uart_drv.h"
#include "uart_cli_task.h"

#include "monitor_task.h"

static void Hardware_Init(void)
{
    /* Set system clock to 120 MHz */
    SysCtlClockFreqSet(
        (SYSCTL_XTAL_25MHZ |
         SYSCTL_OSC_MAIN |
         SYSCTL_USE_PLL |
         SYSCTL_CFG_VCO_480),
        120000000
    );

    /* Enable GPIO Port N */
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPION);
    while (!SysCtlPeripheralReady(SYSCTL_PERIPH_GPION));

    /* Configure PN1 as output */
    GPIOPinTypeGPIOOutput(GPIO_PORTN_BASE, GPIO_PIN_1);
}

int main(void)
{
    Hardware_Init();

    /* Create application tasks */
    HeartbeatTask_Init();

    ButtonTask_Init();

    UART0_Init(115200);
    UART_CLI_TaskInit();

    MonitorTask_Init();

    /* Start FreeRTOS scheduler */
    vTaskStartScheduler();

    /* Should never reach here */
    while (1);
}
