/*
 * LED_CFG.c
 *
 *  Created on: Jun 13, 2023
 *      Author: Muham
 */

#include "LED.h"
#include "../../MCAL/GPIO/GPIO.h"



const ledcfg_t ledcfg[__LED_Length__] =
{
		[led_alarm]={ .LED_PORT =GPIO_PORTA, .LED_PIN=GPIO_PIN2,.Active_State=LED_ACTIVE_HIGH,.name="ALARM"}
		,
		[led_ti_right]={ .LED_PORT =GPIO_PORTA, .LED_PIN=GPIO_PIN3,.Active_State=LED_ACTIVE_HIGH,.name="RIGHT LED"}
		,
		[led_ti_left]={ .LED_PORT =GPIO_PORTA, .LED_PIN=GPIO_PIN4,.Active_State=LED_ACTIVE_HIGH,.name="LEFT LED"}

};



