/*
 * sched.c
 *
 *  Created on: Jun 15, 2023
 *  Author: Muhamed Galal
 */


/******************************************************** Includes ******************************************************************/

#include "sched.h"
#include "../MCAL/SysTick/SysTick.h"

/******************************************************** Defines *************************************************************************/
#define MAX_RUNNABLES   10

/********************************************************* Variables *********************************************************************/
static struct
{
	uint32 size;
	runnable_t  * runnable[MAX_RUNNABLES];
}userRunnables;

/* tick interrupt flag */
static uint8 isReady;

/****************************************************** Static Functions prototype ********************************************************/

static void scheduler(void);
static void schedReady(void);

/****************************************************** Interface functions implementation ************************************************/
void sched_init(void)
{
	SysTick_DelayMS(TICK_MS);
	SysTick_CallBack(schedReady);
}
/*******************************************************************************************************************************************/
void sched_start(void)
{
	SysTick_Start();
	while(1)
	{
		if(isReady)
		{
			isReady=0;
			scheduler();
		}
	}
}
/*******************************************************************************************************************************************/
void sched_registerRunnable(runnable_t * userrunnable)
{
	if (userrunnable != Null)
	{
		if(userRunnables.size <MAX_RUNNABLES)
		{
			/*assign the address of the struct of user "userrunnable" to the pointer of the struct of runnables with priority == userunnable.prioirty*/
			userRunnables.runnable[userrunnable->priority] = userrunnable;
			userRunnables.size++;
		}
	}
}
/*******************************************************************************************************************************************/
/* Static function Implementation */
static void schedReady(void)
{
	isReady=1;
}
/*******************************************************************************************************************************************/
/*every tick execute */
static void scheduler(void)
{
	static uint32 TimeMS;

	/*loop on runnables and check if its time to execute*/
	uint32 idx;
	for(idx=0; idx<MAX_RUNNABLES; idx++)
	{
		if(userRunnables.runnable[idx] !=Null)
		{
			if(TimeMS % userRunnables.runnable[idx]->periodMs == 0)
			{
				/*execute user runnable*/
				userRunnables.runnable[idx]->runnable();
			}
		}
	}
	TimeMS += TICK_MS;
}
