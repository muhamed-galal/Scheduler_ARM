/*
 * LED.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Muham
 */

#include "LED.h"
#include "../../MCAL/GPIO/GPIO.h"


extern const ledcfg_t ledcfg[__LED_Length__];

/********************************************************************************************************************/
extern void LED_Init(void)
{
	gpioPin_t led;
	uint16 index;
	/* set the GPIO mode to Output PushPull */
	led.GPIO_MODE=GPIO_MODE_OUTPUT;
	led.GPIO_OUTPUT_TYPE=GPIO_OUTPUT_TYPE_PUSHPULL;
	led.GPIO_PIN_SPEED=GPIO_PIN_SPEED_LS;

	/* Looping with number of leds in configuration file to set pin and port number */
	for(index=0; index<__LED_Length__; index++)
	{
		led.GPIO_PIN =ledcfg[index].LED_PIN;
		led.GPIO_PORT =ledcfg[index].LED_PORT;
		GPIO_Init(&led);
	}
}
/**********************************************************************************************************************/
extern void LED_SetLedState(uint16 led,uint8 LED_STATE)
{
	/* set the GPIO pin value with led port , led pin and state */
	GPIO_voidSetPinValue(ledcfg[led].LED_PORT, ledcfg[led].LED_PIN, LED_STATE ^ ledcfg[led].Active_State);
}
/*********************************************************************************************************************/
extern void LED_ToggleLED(uint16 led)
{
	GPIO_voidTogglePin(ledcfg[led].LED_PORT, ledcfg[led].LED_PIN);
}

