#include "include/kernel/rosa_task.h"

//void ROSA_tcbCreate(tcb * tcbTask, char tcbName[NAMESIZE], void *tcbFunction, int * tcbStack, int tcbStackSize)

int16_t ROSA_taskCreate(ROSA_taskHandle_t * th, char * id, void * taskFunc, uint32_t stackSize, uint8_t priority)
{
	int16_t result = -1;
	tcb * task;
	int * stack;
	
	if( (task = calloc(1, sizeof(tcb))) && (stack = calloc(DEFAULT_STACK_SIZE, sizeof(int))) )
	{
		task->priority			 = priority;
		task->effective_priority = priority;
		ROSA_tcbCreate(task, id, taskFunc, stack, stackSize);
		ROSA_tcbInstall(task);
		
		result = 0;
	}
	
	return result;
}

int16_t ROSA_taskDelete(ROSA_taskHandle_t tc)
{
	int16_t result = -1;
	
	
	
	return result;
}
