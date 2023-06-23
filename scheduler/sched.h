/*
 * sched.h
 *
 *  Created on: Jun 15, 2023
 *      Author: Muham
 */

#ifndef SCHED_H_
#define SCHED_H_

#include "../Common/STD_TYPES.h"
#include "sched_cfg.h"

typedef struct
{
    void (*runnable)(void);
    uint32 periodMs;
    uint32 priority;
    char * name;
}runnable_t;

/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: sched_registerRunnable																				          *
* Parameters (in)	: runnable_t * userrunnable																					  	  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To register runnables									          									  *
**************************************************************************************************************************************/
extern void sched_registerRunnable(runnable_t * userrunnable);
/**************************************************************************************************************************************
* Function Name		: sched_start																					              	  *
* Parameters (in)	: None																				  							  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To start scheduler									          									      *
**************************************************************************************************************************************/
extern void sched_start(void);
/**************************************************************************************************************************************
* Function Name		: sched_init																					              	  *
* Parameters (in)	: None																				 							  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To initialize scheduler									          								      *
**************************************************************************************************************************************/
extern void sched_init(void);


#endif /* SCHED_H_ */
