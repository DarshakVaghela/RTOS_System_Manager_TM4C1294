/*
 * FreeRTOSConfig.h
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#ifndef RTOS_FREERTOSCONFIG_H_
#define RTOS_FREERTOSCONFIG_H_

#include <stdint.h>

/*-----------------------------------------------------------
 * Forward declarations for assert hook
 *----------------------------------------------------------*/
void vAssertCalled(const char *pcFile, int32_t ulLine);

/*-----------------------------------------------------------
 * RTOS Hook functions
 *----------------------------------------------------------*/
#define configUSE_MALLOC_FAILED_HOOK        1
#define configCHECK_FOR_STACK_OVERFLOW      2

#define configASSERT(x) if ((x) == 0) vAssertCalled(__FILE__, __LINE__)

#define configUSE_TRACE_FACILITY                1
#define configUSE_STATS_FORMATTING_FUNCTIONS    1


/*-----------------------------------------------------------
 * Scheduler configuration
 *----------------------------------------------------------*/
#define configUSE_PREEMPTION            1
#define configUSE_IDLE_HOOK             0
#define configUSE_TICK_HOOK             0

/*-----------------------------------------------------------
 * Clock configuration (TM4C1294 @ 120 MHz)
 *----------------------------------------------------------*/
#define configCPU_CLOCK_HZ              (120000000UL)
#define configTICK_RATE_HZ              ((TickType_t)1000)

/*-----------------------------------------------------------
 * Task configuration
 *----------------------------------------------------------*/
#define configMAX_PRIORITIES            5
#define configMINIMAL_STACK_SIZE        128
#define configMAX_TASK_NAME_LEN         16
#define configUSE_16_BIT_TICKS          0
#define configIDLE_SHOULD_YIELD         1

/*-----------------------------------------------------------
 * Memory configuration
 *----------------------------------------------------------*/
#define configSUPPORT_DYNAMIC_ALLOCATION    1
#define configSUPPORT_STATIC_ALLOCATION     0
#define configTOTAL_HEAP_SIZE               (20 * 1024)

/*-----------------------------------------------------------
 * Synchronization
 *----------------------------------------------------------*/
#define configUSE_MUTEXES               1
#define configUSE_RECURSIVE_MUTEXES     1
#define configUSE_COUNTING_SEMAPHORES   1

/*-----------------------------------------------------------
 * Software timers
 *----------------------------------------------------------*/
#define configUSE_TIMERS                1
#define configTIMER_QUEUE_LENGTH        5
#define configTIMER_TASK_PRIORITY       2
#define configTIMER_TASK_STACK_DEPTH    256

/*-----------------------------------------------------------
 * API inclusion (IMPORTANT)
 *----------------------------------------------------------*/
#define INCLUDE_vTaskPrioritySet        1
#define INCLUDE_uxTaskPriorityGet       1
#define INCLUDE_vTaskDelete             1
#define INCLUDE_vTaskSuspend            1
#define INCLUDE_vTaskDelay              1
#define INCLUDE_vTaskDelayUntil         1
#define INCLUDE_vTaskList               1
#define INCLUDE_vTaskGetInfo             1
#define INCLUDE_xTaskGetSchedulerState  1
#define INCLUDE_xTaskGetIdleTaskHandle  1
#define INCLUDE_xTaskAbortDelay         0

/*-----------------------------------------------------------
 * Cortex-M interrupt priority configuration
 *----------------------------------------------------------*/
#define configKERNEL_INTERRUPT_PRIORITY         (7 << 5)
#define configMAX_SYSCALL_INTERRUPT_PRIORITY    (5 << 5)

/*-----------------------------------------------------------
 * Interrupt handler mapping
 *----------------------------------------------------------*/
#define vPortSVCHandler     SVC_Handler
#define xPortPendSVHandler  PendSV_Handler
#define xPortSysTickHandler SysTick_Handler

#endif /* RTOS_FREERTOSCONFIG_H_ */
