/*
 * EXTI.c
 *
 *  Created on: Jun 3, 2023
 *      Author: Muham
 */

#include "EXTI.h"
#include "../../Common/STD_TYPES.h"
#include "../../Common/util.h"


/* Global array of pointers to function */
static void (* EXTI_CallBack [16] )(void);
/************************************************************************************************************/
/* Defining External interrupt base address*/
#define EXTI_BASEADDRESS 				(0x40013C00)
/**********************************************************************************************************/
/* Defining System configuration EXTICR Registers base address */
#define SYSCFG_EXTICRBASE  				(0x40013808)
/**********************************************************************************************************/
/* system configure register mask */
#define SYSCFG_SHIFT_MASK 4
#define SYSCFG_CLRMASK 0x1111
/**********************************************************************************************************/
/* macro like function to clear the pending  flag in interrupts */
#define EXTI_PENDING_CLR(EXTI_PIN) 		EXTI->PR |=(0x1<<EXTI_PIN)
/**********************************************************************************************************/
typedef struct
{
	volatile uint32 EXTIC[4];
}SYSCFG_EXTIC;

/*********************************************************************************************************/
typedef struct
{
	volatile uint32 IMR;
	volatile uint32 EMR;
	volatile uint32 RTSR;
	volatile uint32 FTSR;
	volatile uint32 SWIER;
	volatile uint32 PR;
}EXTI_t;
/************************************************************************************************************************/
/* pointer to structure  to EXTI registers base address */
static volatile EXTI_t * const EXTI = ((volatile EXTI_t * const)EXTI_BASEADDRESS);

/* pointer to structure  to SYSCFG_EXTIC register base address */
static volatile SYSCFG_EXTIC * const SYSCFG =((volatile SYSCFG_EXTIC * const )SYSCFG_EXTICRBASE);
/***********************************************************************************************************************/

/* Static Functions to  initialize the the callback pointers */
static void CallBackPointer_Init(void);

/***********************************************************************************************************************/
res_t EXTI_Set_InterruptMASK(EXTI_PINS_t EXTI_PIN,uint8 STATE)
{
	res_t result = NoError;
	if (EXTI_PIN >=0 && EXTI_PIN<=15)
	{
		if (STATE == STATE_ENABLE)
		{
			EXTI->IMR |=(0x1<<EXTI_PIN);
		}
		else if( STATE == STATE_DISABLE)
		{
			EXTI->IMR &=~(0x1<<EXTI_PIN);
		}
		else
		{
			/* error */
			result = Error;
		}
	}
	else
	{
		/* Error */
		result = Error;
	}
	return result;
}

res_t EXTI_Set_EventMASK(EXTI_PINS_t EXTI_PIN,uint8 STATE)
{
	res_t result = NoError;

	if (EXTI_PIN >=0 && EXTI_PIN<=15)
	{
		if (STATE == STATE_ENABLE)
		{
			EXTI->EMR |=(0x1<<EXTI_PIN);
		}
		else if( STATE == STATE_DISABLE)
		{
			EXTI->EMR &=~(0x1<<EXTI_PIN);
		}
		else
		{
			/* error */
			result = Error;
		}
	}
	else
	{
		/* Error */
		result = Error;
	}
	return result;

}

res_t EXTI_InterruptTriggrSelection(EXTI_PINS_t EXTI_PIN,uint8 TRIGGER)
{
	res_t result = NoError;

	if (EXTI_PIN >=0 && EXTI_PIN<=15)
	{

		switch(TRIGGER)
		{

		/* Clearing bits of rising and falling registers before select */
		EXTI->FTSR &=~(0x1<<EXTI_PIN);
		EXTI->RTSR &=~(0x1<<EXTI_PIN);

		case TRIGGER_RISING:

			EXTI->RTSR |=(0x1<<EXTI_PIN);
			break;
		case TRIGGER_FALLING:

			EXTI->FTSR |=(0x1<<EXTI_PIN);
			break;

		case TRIGGER_ONCHANGE:

			EXTI->RTSR |=(0x1<<EXTI_PIN);
			EXTI->FTSR |=(0x1<<EXTI_PIN);
			break;
		default:
			/* Error*/
			break;
		}
	}
	else
	{
		/* Error */
		result = Error;
	}
	return result;

}

res_t EXTI_Set_SWInterruptState(EXTI_PINS_t EXTI_PIN)
{
	res_t result = NoError;

	if (EXTI_PIN >=0 && EXTI_PIN<=15)
	{
		EXTI->SWIER |=(0x1<<EXTI_PIN);
	}
	else
	{
		/* Error */
		result = Error;
	}
	return result;

}

res_t EXTI_voidSetEXTIConfig(EXTI_PINS_t EXTI_PIN,uint8 EXTI_PORT)
{
	res_t result = NoError;

	if (EXTI_PIN >=0 && EXTI_PIN<=15)
	{
		/* Clearing the 4 bits of interrupt selecting port
		 * getting the register number  from 0 to 3  and get the bits number with shifting pin number*/
		SYSCFG->EXTIC[EXTI_PIN / SYSCFG_SHIFT_MASK] &=~(SYSCFG_CLRMASK <<( (EXTI_PIN % SYSCFG_SHIFT_MASK ) * SYSCFG_SHIFT_MASK));
		SYSCFG->EXTIC[EXTI_PIN / SYSCFG_SHIFT_MASK] |= (EXTI_PORT << ((EXTI_PIN % SYSCFG_SHIFT_MASK ) * SYSCFG_SHIFT_MASK));
	}
	else
	{
		/* Error */
		result = Error;

	}
	return result;

}


res_t EXTI_voidCallBack(EXTI_PINS_t EXTI_PIN, void (*ptr) (void))
{
	res_t result = NoError;

	CallBackPointer_Init();
	if (ptr != Null)
	{
		EXTI_CallBack[EXTI_PIN]	= ptr;
	}
	else
	{
		result = Error;
	}

	return result;

}


void EXTI0_IRQHandler(void) // ISR
{
	if (EXTI_CallBack[0] != Null)
		EXTI_CallBack[0]();
	/* clear pending flag */
	EXTI_PENDING_CLR(EXTI_PIN0);
}

void EXTI1_IRQHandler(void) // ISR
{
	if (EXTI_CallBack[1] != Null)
		EXTI_CallBack[1]();

	/* clear pending flag */
	EXTI_PENDING_CLR(EXTI_PIN1);
}



static void CallBackPointer_Init(void)
{
	for (uint8 count=0;count<16;count++)
	{
		if (EXTI_CallBack [count] == 0)
			EXTI_CallBack [count]= Null;
	}
}
