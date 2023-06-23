/*
 * GPIO.H
 *
 *  Created on: May 26, 2023
 *      Author: Muham
 */

#ifndef GPIO_GPIO_H_
#define GPIO_GPIO_H_

#include "../../Common/STD_TYPES.h"


/*****************************************************Function :GPIO_voidSetPinMode**************************************************/
#define GPIO_PORTA						0
#define GPIO_PORTB						1
#define GPIO_PORTC						2
/*************************************************************************************************************************************/
#define GPIO_PIN0						0
#define GPIO_PIN1						1
#define GPIO_PIN2						2
#define GPIO_PIN3						3
#define GPIO_PIN4						4
#define GPIO_PIN5						5
#define GPIO_PIN6						6
#define GPIO_PIN7						7
#define GPIO_PIN8						8
#define GPIO_PIN9						9
#define GPIO_PIN10						10
#define GPIO_PIN11						11
#define GPIO_PIN12						12
#define GPIO_PIN13						13
#define GPIO_PIN14						14
#define GPIO_PIN15						15
#define GPIO_PIN16						16
/********************************************************** GPIO PIN MODES  ***********************************************************/
#define GPIO_MODE_INPUT 				0
#define GPIO_MODE_OUTPUT 				1
#define GPIO_MODE_ALTERNATE 			2
#define GPIO_MODE_ANALOG 				3
/*********************************************************  GPIO PIN VALUES **********************************************************/
#define GPIO_VALUE_HIGH					1
#define GPIO_VALUE_LOW					0
/*********************************************************  GPIO PIN Output TYPE **********************************************************/
#define GPIO_OUTPUT_TYPE_PUSHPULL		0
#define GPIO_OUTPUT_TYPE_OPENDRAIN 		1
/********************************************************** GPIO PIN SPEED **********************************************************/
#define GPIO_PIN_SPEED_LS				0
#define GPIO_PIN_SPEED_MS				1
#define GPIO_PIN_SPEED_HS				2
#define GPIO_PIN_SPEED_EHS				3
/*********************************************************** GPIO PIN Input TYPES *******************************************************/
#define GPIO_INPUT_TYPE_NOPULL			0
#define GPIO_INPUT_TYPE_PULLUP			1
#define GPIO_INPUT_TYPE_PULLDOWN		2
/****************************************************************************************************************************************/
typedef struct
{
	uint8 GPIO_PORT;
	uint8 GPIO_PIN;
	uint8 GPIO_MODE;
	uint8 GPIO_OUTPUT_TYPE;
	uint8 GPIO_INPUT_TYPE;
	uint8 GPIO_PIN_SPEED;
}gpioPin_t;

/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
 * Function Name		: GPIO_Init																							              *
 * Parameters (in)	: gpioPin_t * pincfg																							  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To initialize GPIO pin								          									      *
 **************************************************************************************************************************************/
void GPIO_Init(gpioPin_t * pincfg);
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidSetPinValue																				              *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE																  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To Set pin value									          										      *
 **************************************************************************************************************************************/
void GPIO_voidSetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE);
/**************************************************************************************************************************************
 * Function Name	: GPIO_voidTogglePin																				              *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE																  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To toggle pin value									       										      *
 **************************************************************************************************************************************/
void GPIO_voidTogglePin(uint8 GPIO_PORT,uint8 GPIO_PIN);
/**************************************************************************************************************************************
 * Function Name		: GPIO_uint8GetPinValue																				          *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN																			      *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To read pin value								          										      *
 **************************************************************************************************************************************/
uint8 GPIO_uint8GetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN);
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidAtomicSetPinValue																		          *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE																  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To atomic Set pin value									          								      *
 **************************************************************************************************************************************/
void GPIO_voidAtomicSetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE);




/* static functions prototypes */
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidSetPinMode																				          *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_MODE																  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To Set pin mode										          										  *
 **************************************************************************************************************************************/
 void GPIO_voidSetPinMode(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_MODE);
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidSetOutputType																				      *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_OUTPUT_TYPE														  *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To Set output type (push pull / open drain)								          			          *
 **************************************************************************************************************************************/
 void GPIO_voidSetOutputType(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_OUTPUT_TYPE);
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidSetPinSpeed																				          *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_PIN_SPEED														      *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To Set pin speed									          										      *
 **************************************************************************************************************************************/
 void GPIO_voidSetPinSpeed(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_PIN_SPEED);
/**************************************************************************************************************************************
 * Function Name		: GPIO_voidSetInputType																				          *
 * Parameters (in)	: uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_INPUT_TYPE)													      *
 * Parameters (out)	: None																						                      *
 * Return value		: None							  															    	              *
 * Description		: Function To Set port type (No pull up or pull down,  pull up , pull down)								      	  *
 **************************************************************************************************************************************/
 void GPIO_voidSetInputType(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_INPUT_TYPE);


#endif /* GPIO_GPIO_H_ */
