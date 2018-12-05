#include "semaphore.h"
#include "queue.h"
#include "doubly_linked_list.h"
#include "include/kernel/rosa_ker.h"
#include "include/kernel/rosa_scheduler.h"
#include <stdio.h>

//check this function later
int16_t ROSA_semaphoreCreate(ROSA_semaphoreHandle_t * handle, uint8_t ceiling)
{
	int16_t result = -1;
	if (handle == NULL)
	{
		return result;
	}
	else
	{
		handle = calloc(1, sizeof(ROSA_semaphoreHandle_t));
		handle->flag = 0;		// 0 when semaphore is not locked, 1 when semaphore is locked
		handle->ceiling = ceiling;
		handle->current_task = NULL;
		handle->task_priority = 0;
		handle->waiting_tasks = calloc(1,sizeof(queue));		
		if ( init_queue(handle->waiting_tasks) )   //CHECK HERE
		{
			return result;
		}
		result = 0;
		return result;
	}
}

int16_t ROSA_semaphoreDelete(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(&handle && is_empty(handle.waiting_tasks) == 1 && handle.flag == 0 && handle.current_task == NULL)
	{
		free(handle.waiting_tasks);
		free(&handle);
		result = 0;
		return result;
	}
	return result;
}

int16_t ROSA_semaphorePeek(ROSA_semaphoreHandle_t handle)
{
	return handle.flag;
}

int16_t ROSA_semaphoreLock(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(handle.flag == 0)
	{
		// If the semaphore is not locked, executing task can lock it
		// Task inherits the priority ceiling of the semaphore
		// Dynamic priority of the task is changed if priority of the task is lower than the ceiling of the semaphore
		
		handle.flag = 1;
		handle.current_task = EXECTASK;
		handle.task_priority = EXECTASK->effective_priority; 
		if(EXECTASK->effective_priority > handle.ceiling)
		{			
			EXECTASK->effective_priority = handle.ceiling;			
		}
		
		//task inherits the priority of the semaphore if prio(task) < ceil(sem)
	}
	else if(handle.flag == 1)
	{
		// If the semaphore is locked, executing task cannot lock it
		// Task is put into the waiting queue for the specific semaphore 
		// Task is also removed from the ready list
		
		enqueue(handle.waiting_tasks, EXECTASK);
		remove_tcb(EXECTASK);
		  
	}
}

int16_t ROSA_semaphoreUnlock(ROSA_semaphoreHandle_t handle)
{
	int16_t result = -1;
	if(handle.flag == 0)
	{
		return result;
	}
	else 
	{
		// Checks if the task that locked the semaphore is the task that wants to unlock it, if not return error 
		// Changes the status of the semaphore to unlocked (flag = 0), if the queue of waiting tasks is empty
		// Clears the pointer to the task that was currently holding the semaphore
		// If the queue of waiting tasks is not empty, it takes the first task from the queue and that task can lock the semaphore
		// The task is removed from the queue and put into the ready list
		if(handle.current_task == EXECTASK)
		{
			if(is_empty(handle.waiting_tasks) == 1)
			{
				handle.flag = 0;
				EXECTASK->effective_priority = handle.task_priority;
				handle.current_task = NULL;
				
			}
			else
			{
				EXECTASK->effective_priority = handle.task_priority;
				tcb * tmp_tcb;
				dequeue(handle.waiting_tasks, tmp_tcb);
				handle.current_task = tmp_tcb;
				handle.task_priority = tmp_tcb->effective_priority; 
				if(tmp_tcb->effective_priority > handle.ceiling)
				{
					tmp_tcb->effective_priority = handle.ceiling;
				}
				insert_by_priority(ready_list, tmp_tcb);
			}
			result = 0;
			return result;
		}
		else
		return result;
	}
}