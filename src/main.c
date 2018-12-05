/*****************************************************************************

                 ,//////,   ,////    ,///' /////,
                ///' ./// ///'///  ///,    ,, //
               ///////,  ///,///   '/// ///''\\,
             ,///' '///,'/////',/////'  /////'\\,

    Copyright 2010 Marcus Jansson <mjansson256@yahoo.se>

    This file is part of ROSA - Realtime Operating System for AVR32.

    ROSA is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    ROSA is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with ROSA.  If not, see <http://www.gnu.org/licenses/>.
*****************************************************************************/
/* Tab size: 4 */

//Standard library includes
#include <avr32/io.h>

//Kernel includes
#include "kernel/rosa_ker.h"

//Driver includes
#include "drivers/led.h"
#include "drivers/delay.h"
#include "drivers/usart.h"

//Include configuration
#include "rosa_config.h"

#include "kernel/semaphore.h"
#include "include/kernel/rosa_task.h"


ROSA_semaphoreHandle_t S1;
ROSA_semaphoreHandle_t S2;

ROSA_taskHandle_t A;
ROSA_taskHandle_t B;

void taskA(void)
{
	while(1)
	{
		ledToggle(LED0_GPIO);
		ledToggle(LED0_GPIO);
		ledToggle(LED0_GPIO);
		//ledOn(LED0_GPIO);
		//ROSA_delay(2000);
		//ledOff(LED0_GPIO);
	}
}

void taskB(void)
{
	while(1)
	{
		ledOn(LED1_GPIO);
		ROSA_delay(5000);
		ledOff(LED1_GPIO);
	}
}
/*
void taskA(void)
{
	while(1)
	{
		ROSA_semaphoreLock(S1);
		ledOn(LED0_GPIO);
		ROSA_delay(2000);
		//ROSA_semaphoreUnlock(S1);
	}
}

void taskB(void)
{
	while(1)
	{
		if(ROSA_semaphoreUnlock(S1)==0)
		{
			ledOff(LED0_GPIO);
			
		}
	}
}
*/


/*************************************************************
 * Main function
 ************************************************************/
int main(void)
{
	//Initialize the ROSA kernel
	ROSA_init();
	
	ROSA_taskCreate(A, "taskA", taskA, 40, 1);

	//Start the ROSA kernel
	ROSA_start();
	

	/* Execution will never return here */
	while(1);
}
