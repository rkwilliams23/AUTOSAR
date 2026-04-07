#ifndef OSAL_H
#define OSAL_H

#include <stdint.h>
#include "osal_types.h"

void osal_init(void);

void osal_task_create(osal_task_func_t func, void *arg);

void osal_delay(uint32_t ms);

#endif
