/*
 * LED.h
 *
 *  Created on: Jun 13, 2023
 *      Author: Muham
 */

#ifndef LED_LED_H_
#define LED_LED_H_

#include "../../Common/STD_TYPES.h"
#include "LED_CFG.h"

/* LED States */
#define LED_STATE_ON  0
#define LED_STATE_OFF 1

/* used in led configuration */
#define LED_ACTIVE_HIGH	1
#define LED_ACTIVE_LOW  0


typedef struct
{
	uint8 LED_PORT;
	uint8 LED_PIN;
	uint8 Active_State;
	char * name;
}ledcfg_t;

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
extern void LED_SetLedState(uint16 Led,uint8 State);
/**************************************************************************************************************************************
* Function Name		: LED_Init																							              *
* Parameters (in)	: None																											  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To initialize LED									          									      *
**************************************************************************************************************************************/
extern void LED_Init(void);
/**************************************************************************************************************************************
* Function Name		: LED_ToggleLED																							          *
* Parameters (in)	: None																											  *
* Parameters (out)	: None																						                      *
* Return value		: None							  															    	              *
* Description		: Function To toggle LED state								          									          *
**************************************************************************************************************************************/
extern void LED_ToggleLED(uint16 Led);

#endif /* LED_LED_H_ */
