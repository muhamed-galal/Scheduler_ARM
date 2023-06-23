/*
 * EXTI.h
 *
 *  Created on: Jun 3, 2023
 *      Author: Muham
 */

#ifndef EXTI_EXTI_H_
#define EXTI_EXTI_H_

#include "../../Common/STD_TYPES.h"
#include "../../Common/util.h"

/**************************************** EXTI PINS***********************************************************/
typedef enum
{

	EXTI_PIN0	,
	EXTI_PIN1	,
	EXTI_PIN2	,
	EXTI_PIN3	,
	EXTI_PIN4	,
	EXTI_PIN5	,
	EXTI_PIN6	,
	EXTI_PIN7	,
	EXTI_PIN8	,
	EXTI_PIN9	,
	EXTI_PIN10	,
	EXTI_PIN11	,
	EXTI_PIN12	,
	EXTI_PIN13	,
	EXTI_PIN14	,
	EXTI_PIN15

}EXTI_PINS_t;

/********************************** Defining States********************************************************/
#define STATE_ENABLE  1
#define STATE_DISABLE 0
/*********************************************************************************************************/
/********************************** Defining Triggers ****************************************************/
#define TRIGGER_RISING	 0
#define TRIGGER_FALLING  1
#define TRIGGER_ONCHANGE 2
/******************************************* Port select for EXTI ****************************************/
#define EXTI_PORTA 	0
#define EXTI_PORTB	1
#define EXTI_PORTC	2
/*************************************** Functions Prototypes **************************************/
/***************************************************************************************************
 * Function Name         : EXTI_Set_EXTI_MASK                                           			*
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Setting EXTI interrupt mask state                                        *
 ***************************************************************************************************/
res_t EXTI_Set_InterruptMASK(EXTI_PINS_t EXTI_PIN,uint8 STATE);
/***************************************************************************************************
 * Function Name         : EXTI_Set_EXTI_EventMASK                                          		*
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Setting EXTI Event mask state                                            *
 ***************************************************************************************************/
res_t EXTI_Set_EventMASK(EXTI_PINS_t EXTI_PIN,uint8 STATE);
/***************************************************************************************************
 * Function Name         : EXTI_InterruptTriggrSelection                                   		    *
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Select triggering option                                                 *
 ***************************************************************************************************/
res_t EXTI_InterruptTriggrSelection(EXTI_PINS_t EXTI_PIN,uint8 TRIGGER);
/***************************************************************************************************
 * Function Name         : EXTI_Set_SWInterruptState                                          	    *
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Setting EXTI software interrupt request                                  *
 ***************************************************************************************************/
res_t EXTI_Set_SWInterruptState(EXTI_PINS_t EXTI_PIN);
/***************************************************************************************************
 * Function Name         : EXTI_voidSetEXTIConfig                                          	  	    *
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Setting EXTI software interrupt request                                  *
 ***************************************************************************************************/
res_t EXTI_voidSetEXTIConfig(EXTI_PINS_t EXTI_PIN,uint8 EXTI_PORT);
/***************************************************************************************************
 * Function Name         : EXTI_voidCallBack                                          	   			*
 * Input Parameters(in)  : None                                                                     *
 * Output Parameter(out) : None                                                                     *
 * Return value          : None                                                                     *
 * Functionality         : Setting EXTI software interrupt request                                  *
 ***************************************************************************************************/
res_t EXTI_voidCallBack(EXTI_PINS_t EXTI_PIN, void (*ptr) (void));






#endif /* EXTI_EXTI_H_ */
