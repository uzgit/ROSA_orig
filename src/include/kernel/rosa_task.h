#include "rosa_def.h"
#include <stdint.h>
#include <stdlib.h>

#ifndef ROSA_TASK_H
#define ROSA_TASK_H

#define DEFAULT_STACK_SIZE 0x40
#define ROSA_taskHandle_t tcb*

int16_t ROSA_taskCreate(ROSA_taskHandle_t *, char * id, void *, uint32_t, uint8_t);
int16_t ROSA_taskDelete(ROSA_taskHandle_t);

#endif
