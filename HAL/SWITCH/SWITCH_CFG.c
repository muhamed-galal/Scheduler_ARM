/*
 * SWITCH_CFG.c
 *
 *  Created on: Jun 14, 2023
 *      Author: Muham
 */
#include "SWITCH.h"
#include "../../MCAL/GPIO/GPIO.h"

const SWcfg_t switchcfg[__Switch_Length__] =
{
		[switch_li_door]={ .switch_PORT =GPIO_PORTA, .switch_PIN=GPIO_PIN0,.switch_active_state=SWITCH_ACTIVE_LOW,.name="Left Door"}
		,
		[switch_ri_door]={ .switch_PORT =GPIO_PORTA, .switch_PIN=GPIO_PIN1,.switch_active_state=SWITCH_ACTIVE_LOW,.name="Right Door"}

};


