/*
 * rtos_hooks.h
 *
 *  Created on: 30-Dec-2025
 *      Author: darshak
 */

#ifndef RTOS_RTOS_HOOKS_H_
#define RTOS_RTOS_HOOKS_H_

#include <stdint.h>   /* REQUIRED for int32_t */

void vApplicationMallocFailedHook(void);
void vApplicationStackOverflowHook(void *xTask, char *pcTaskName);
void vAssertCalled(const char *pcFile, int32_t ulLine);

#endif /* RTOS_RTOS_HOOKS_H_ */
