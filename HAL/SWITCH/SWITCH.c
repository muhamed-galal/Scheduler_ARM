/*
 * SWITCH.c
 *
 *  Created on: Jun 14, 2023
 *      Author: Muham
 */



#include "SWITCH.h"
#include "../../MCAL/GPIO/GPIO.h"


extern const SWcfg_t switchcfg[__Switch_Length__];

/********************************************************************************************************************/
extern void SWITCH_Init(void)
{
	gpioPin_t SW;
	uint16 index;
	/* set the GPIO mode to input  */
	SW.GPIO_MODE=GPIO_MODE_INPUT;
	SW.GPIO_PIN_SPEED=GPIO_PIN_SPEED_LS;

	/* Looping with number of switchs in configuration file to set pin and port number */
	for(index=0; index<__Switch_Length__; index++)
	{
		SW.GPIO_PIN =switchcfg[index].switch_PIN;
		SW.GPIO_PORT =switchcfg[index].switch_PORT;

		/* check if the switch  is  active low so  GPIO input type is pull up */
		if(switchcfg[index].switch_active_state== SWITCH_ACTIVE_LOW)
			SW.GPIO_INPUT_TYPE=GPIO_INPUT_TYPE_PULLUP;
		else
			SW.GPIO_INPUT_TYPE=GPIO_INPUT_TYPE_PULLDOWN;

		GPIO_Init(&SW);
	}
}
/**********************************************************************************************************************/
extern int SWITCH_GetSwitchState(uint16 Switch)
{
	uint8 res;
	/* set the GPIO pin value with led port , led pin and state */
	res= GPIO_uint8GetPinValue(switchcfg[Switch].switch_PORT, switchcfg[Switch].switch_PIN) ^ (switchcfg[Switch].switch_active_state);


	return res;
}
/*********************************************************************************************************************/





