#include "include/kernel/rosa_task.h"
#include "include/kernel/rosa_ker.h"

//void ROSA_tcbCreate(tcb * tcbTask, char tcbName[NAMESIZE], void *tcbFunction, int * tcbStack, int tcbStackSize)

int16_t ROSA_taskCreate(ROSA_taskHandle_t * th, char * id, void * taskFunc, uint32_t stackSize, uint8_t priority)
{
	int16_t result = -1;
	tcb * task;
	int * stack;
	
	task = malloc(sizeof(tcb));
	stack = malloc(DEFAULT_STACK_SIZE * sizeof(int));
	
	if( (task != NULL) && (stack != NULL) )
	{
		th = malloc(sizeof(tcb*));
		task = malloc(sizeof(tcb));
		//stack = malloc(sizeof(int));
		
		th = & task;
		
		task->priority			 = priority;
		task->effective_priority = priority;
		ROSA_tcbCreate(task, id, taskFunc, stack, stackSize);
		ROSA_tcbInstall(task);
		
		result = 0;
	}
	
	return result;
}

int16_t ROSA_taskDelete(ROSA_taskHandle_t th)
{
	int16_t result = -1;
	
	if(th != 0)
	{
		free(th->dataarea);
		free(th);
		
		result = 0;
	}
	
	return result;
}