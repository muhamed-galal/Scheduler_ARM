/*
 * SWITCH.h
 *
 *  Created on: Jun 14, 2023
 *      Author: Muham
 */

#include "../../Common/STD_TYPES.h"
#include "SWITCH_CFG.h"



/* used in led configuration */
#define SWITCH_ACTIVE_HIGH	0				// GPIO PullDown
#define SWITCH_ACTIVE_LOW  1				// GPIO PullUP

typedef struct
{
	uint8 switch_PORT;
	uint8 switch_PIN;
	uint8 switch_active_state;
	char * name;
}SWcfg_t;

/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: LED_SetLedState																					              *
* Parameters (in)	: uint16 Led,uint8 State																						  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To set led state										          									      *
**************************************************************************************************************************************/
extern int SWITCH_GetSwitchState(uint16 Switch );
/**************************************************************************************************************************************
* Function Name		: LED_Init																							              *
* Parameters (in)	: None																											  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To initialize LED									          									      *
**************************************************************************************************************************************/
extern void SWITCH_Init(void);
