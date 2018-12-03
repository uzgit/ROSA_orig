#include "rosa_def.h"

#ifndef TASK_H
#define TASK_H

#define ROSA_taskHandle_t tcb*

int16_t ROSA_taskCreate(ROSA_taskHandle_t *, char * id, void *, uint32_t, uint8_t);
int16_t ROSA_taskDelete(ROSA_taskHandle);

#endif
