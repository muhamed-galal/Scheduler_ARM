/*
 * GPIO.c
 *
 *  Created on: May 26, 2023
 *      Author: Muham
 */


/* Defines */

#include "GPIO.h"
#include "../../Common/STD_TYPES.h"

#define GPIOA_BaseAddress     0x40020000
#define GPIOB_BaseAddress     0x40020400
#define GPIOC_BaseAddress     0x40020800

#define GPIO_MODE_MASK 			3

#define GPIO_ATOMIC_RESET_START 16


/* Typedefs */

typedef struct
{
	volatile uint32 MODER;
	volatile uint32 OTYPER;
	volatile uint32 OSPEEDR;
	volatile uint32 PUPDR;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 LCKR;
	volatile uint32 AFRL;
	volatile uint32 AFRH;

}GPIO_t;

/* variables */

static volatile GPIO_t * const GPIOA = (volatile GPIO_t * const) GPIOA_BaseAddress ;

static volatile GPIO_t * const GPIOB = (volatile GPIO_t * const) GPIOB_BaseAddress ;

static volatile GPIO_t * const GPIOC = (volatile GPIO_t * const) GPIOC_BaseAddress ;


/*************************************************************************************************************************************/
/* Interface Functions Implementation */
/*************************************************************************************************************************************/
void GPIO_Init(gpioPin_t * pincfg)
{
	GPIO_voidSetPinMode( pincfg->GPIO_PORT, pincfg->GPIO_PIN, pincfg->GPIO_MODE);
	if (pincfg->GPIO_MODE == GPIO_MODE_INPUT)
		GPIO_voidSetInputType(pincfg->GPIO_PORT,pincfg-> GPIO_PIN, pincfg-> GPIO_INPUT_TYPE);
	if (pincfg->GPIO_MODE == GPIO_MODE_OUTPUT)
		GPIO_voidSetOutputType(pincfg->GPIO_PORT, pincfg->GPIO_PIN, pincfg->GPIO_OUTPUT_TYPE);
	GPIO_voidSetPinSpeed(pincfg->GPIO_PORT,pincfg-> GPIO_PIN,pincfg-> GPIO_PIN_SPEED);
}
/*****************************************************************************************************************************************************/
void GPIO_voidSetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE)
{
	switch(GPIO_PORT)
	{

	case GPIO_PORTA :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOA->ODR |= (1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOA->ODR &=~(1<<(GPIO_PIN));
		}
		break;


	case GPIO_PORTB :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOB->ODR |= (1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOB->ODR &=~(1<<(GPIO_PIN));
		}
		break;


	case GPIO_PORTC :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOC->ODR |= (1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOC->ODR &=~(1<<(GPIO_PIN));
		}
		break;
	}
}
/**************************************************************************************************************************************************/
void GPIO_voidTogglePin(uint8 GPIO_PORT,uint8 GPIO_PIN)
{
	switch(GPIO_PORT)
	{

	case GPIO_PORTA :
		GPIOA->ODR ^= (1<<(GPIO_PIN));
		break;
	case GPIO_PORTB :
		GPIOB->ODR ^= (1<<(GPIO_PIN));
		break;
	case GPIO_PORTC :
		GPIOC->ODR ^= (1<<(GPIO_PIN));
		break;
	}
}
/*****************************************************************************************************************************************************/
uint8 GPIO_uint8GetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN)
{
	uint8 ReadPinValue;
	switch(GPIO_PORT)
	{
	case GPIO_PORTA :ReadPinValue = (uint8)((GPIOA->IDR >> GPIO_PIN )& 0x1); break;
	case GPIO_PORTB :ReadPinValue = (uint8)((GPIOB->IDR >> GPIO_PIN )& 0x1); break;
	case GPIO_PORTC :ReadPinValue = (uint8)((GPIOC->IDR >> GPIO_PIN )& 0x1); break;
	}
	return ReadPinValue;
}
/*****************************************************************************************************************************************************/
void GPIO_voidAtomicSetPinValue(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_VALUE)
{
	switch(GPIO_PORT)
	{

	case GPIO_PORTA :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOA->BSRR = (0x1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOA->BSRR = (0x1<<(GPIO_PIN+GPIO_ATOMIC_RESET_START));
		}
		break;


	case GPIO_PORTB :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOB->BSRR = (1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOB->BSRR = (1<<(GPIO_PIN+GPIO_ATOMIC_RESET_START));
		}
		break;

	case GPIO_PORTC :
		if (GPIO_VALUE== GPIO_VALUE_HIGH)
		{
			GPIOC->BSRR = (1<<(GPIO_PIN));
		}
		else if (GPIO_VALUE== GPIO_VALUE_LOW)
		{
			GPIOC->BSRR = (1<<(GPIO_PIN+GPIO_ATOMIC_RESET_START));
		}
		break;
	}

}
/*****************************************************************************************************************************************************/
/* Static Functions Implementation */
/**************************************************************************************************************************************************/
 void GPIO_voidSetPinMode(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_MODE)
{
	uint32 temp;
	switch(GPIO_PORT)
	{

	case GPIO_PORTA :
		temp = GPIOA->MODER;
		temp &=~(GPIO_MODE_MASK<<(GPIO_PIN*2));

		temp |=(GPIO_MODE<<(GPIO_PIN*2));
		GPIOA->MODER = temp;
		break;

	case GPIO_PORTB :
		temp = GPIOB->MODER;
		temp &=~(GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |=(GPIO_MODE<<(GPIO_PIN*2));
		GPIOB->MODER = temp;
		break;

	case GPIO_PORTC :
		temp = GPIOC->MODER;
		temp &=~(GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |=(GPIO_MODE<<(GPIO_PIN*2));
		GPIOC->MODER = temp;
		break;

	}
}
/*****************************************************************************************************************************************************/
 void GPIO_voidSetOutputType(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_OUTPUT_TYPE)
{
	switch(GPIO_PORT)
	{

	case GPIO_PORTA :
		if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_OPENDRAIN)
		{
			GPIOA->OTYPER |= (1<<(GPIO_PIN));
		}
		else if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_PUSHPULL)
		{
			GPIOA->OTYPER &=~(1<<(GPIO_PIN));
		}
		break;
	case GPIO_PORTB :
		if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_OPENDRAIN)
		{
			GPIOB->OTYPER |= (1<<(GPIO_PIN));
		}
		else if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_PUSHPULL)
		{
			GPIOB->OTYPER &=~(1<<(GPIO_PIN));
		}
		break;

	case GPIO_PORTC :
		if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_OPENDRAIN)
		{
			GPIOC->OTYPER |= (1<<(GPIO_PIN));
		}
		else if (GPIO_OUTPUT_TYPE== GPIO_OUTPUT_TYPE_PUSHPULL)
		{
			GPIOC->OTYPER &=~(1<<(GPIO_PIN));
		}
		break;
	}
}
/*****************************************************************************************************************************************************/
 void GPIO_voidSetPinSpeed(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_PIN_SPEED)
{
	uint32 temp ;
	switch(GPIO_PORT)
	{
	case GPIO_PORTA :
		temp = GPIOA->OSPEEDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_PIN_SPEED<<(GPIO_PIN*2));
		GPIOA->OSPEEDR = temp;
		break;

	case GPIO_PORTB :
		temp = GPIOB->OSPEEDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_PIN_SPEED<<(GPIO_PIN*2));
		GPIOB->OSPEEDR = temp;
		break;

	case GPIO_PORTC :
		temp = GPIOC->OSPEEDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_PIN_SPEED<<(GPIO_PIN*2));
		GPIOC->OSPEEDR = temp;
		break;
	}

}
/*****************************************************************************************************************************************************/
 void GPIO_voidSetInputType(uint8 GPIO_PORT,uint8 GPIO_PIN, uint8 GPIO_INPUT_TYPE)
{
	uint32 temp;
	switch(GPIO_PORT)
	{
	case GPIO_PORTA :
		temp = GPIOA->PUPDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_INPUT_TYPE<<(GPIO_PIN*2));
		GPIOA->PUPDR = temp;
		break;

	case GPIO_PORTB :
		temp = GPIOB->PUPDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_INPUT_TYPE<<(GPIO_PIN*2));
		GPIOB->PUPDR = temp;
		break;

	case GPIO_PORTC :
		temp = GPIOC->PUPDR;
		temp &=~ (GPIO_MODE_MASK<<(GPIO_PIN*2));
		temp |= (GPIO_INPUT_TYPE<<(GPIO_PIN*2));
		GPIOC->PUPDR = temp;
		break;
	}
}
