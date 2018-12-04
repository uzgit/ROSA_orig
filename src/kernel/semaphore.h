#include "queue.h"
#include "doubly_linked_list.h"
#include <stdio.h>

#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

typedef struct
{
	int flag;
	uint8_t ceiling;
	tcb * current_task;
	queue * waiting_tasks;	
} ROSA_semaphoreHandle_t;

int16_t ROSA_semaphoreCreate(ROSA_semaphoreHandle_t * handle, uint8_t ceiling);
int16_t ROSA_semaphoreDelete(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphorePeek(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphoreLock(ROSA_semaphoreHandle_t handle);
int16_t ROSA_semaphoreUnlock(ROSA_semaphoreHandle_t handle);



#endif /* SEMAPHORE_H_ */