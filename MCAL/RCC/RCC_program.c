/*
 * RCC_program.c
 *
 *  Created on: May 21, 2023
 *      Author: Muham
 */

/*Include */


#include "../../Common/STD_TYPES.h"
#include "../../Common/util.h"
#include "RCC_interface.h"



/* Defines */

#define RCC_BaseAddress     0x40023800

/* Types */

typedef struct
{
	volatile uint32 RCC_CR;
	volatile uint32 RCC_PLLCFGR;
	volatile uint32 RCC_CFGR;
	volatile uint32 RCC_CIR;
	volatile uint32 RCC_AHB1RSTR;
	volatile uint32 RCC_AHB2RSTR;
	volatile uint32 Reserved1;
	volatile uint32 Reserved2;
	volatile uint32 RCC_APB1RSTR;
	volatile uint32 RCC_APB2RSTR;
	volatile uint32 Reserved3;
	volatile uint32 Reserved4;
	volatile uint32 RCC_AHB1ENR;
	volatile uint32 RCC_AHB2ENR;
	volatile uint32 Reserved5;
	volatile uint32 Reserved6;
	volatile uint32 RCC_APB1ENR;
	volatile uint32 RCC_APB2ENR;
	volatile uint32 Reserved7;
	volatile uint32 Reserved8;
	volatile uint32 RCC_AHB1LPENR;
	volatile uint32 RCC_AHB2LPENR;
	volatile uint32 Reserved9;
	volatile uint32 Reserved10;
	volatile uint32 RCC_APB1LPENR;
	volatile uint32 RCC_APB2LPENR;
	volatile uint32 Reserved11;
	volatile uint32 Reserved12;
	volatile uint32 RCC_BDCR;
	volatile uint32 RCC_CSR;
	volatile uint32 Reserved13;
	volatile uint32 Reserved14;
	volatile uint32 RCC_SSCGR;
	volatile uint32 RCC_PLLI2SCFGR;
	volatile uint32 Reserved15;
	volatile uint32 RCC_DCKCFGR;

}RCC_REGS;

/* Variables */

static volatile RCC_REGS * const RCC = (volatile RCC_REGS * const) RCC_BaseAddress ;


/* Static Functions prototype */

/* Interface Implementation Functions */

res_t MRCC_voidSetCLKSatus(uint32 CLK, uint8 STATUS)
{
	res_t ErrState = NoError;
	/*Switch on the Clock Source which one*/
	switch(CLK)
	{
	case CLK_HSI:
		/*Switch The Status Wanted Enable Or Disable*/
		switch(STATUS)
		{
		case STATUS_ENABLE:

			/*Enable The HSI Clock Source*/
			RCC->RCC_CR |=CLK_HSI;
			break;

		case STATUS_DISABLE:

			/*Disable The HSI Clock Source*/
			RCC->RCC_CR &=~CLK_HSI;
			break;
		default:
			/* input : status Error*/
			ErrState=Error;
			break;
		}
		break;

		case CLK_HSE:

			/*Switch The Status Wanted Enable Or Disable*/
			switch(STATUS)
			{
			case STATUS_ENABLE:

				/*Enable The HSE Clock Source*/
				RCC->RCC_CR |=CLK_HSE;
				break;

			case STATUS_DISABLE:

				/*Disable The HSE Clock Source*/
				RCC->RCC_CR &=~ CLK_HSE;
				break;

			default:
				/* input : status Error*/
				ErrState=Error;
				break;
			}
			break;

			case CLK_PLL:

				/*Switch The Status Wanted Enable Or Disable*/
				switch(STATUS)
				{
				case STATUS_ENABLE:

					/*Enable The PLL Clock Source*/
					RCC->RCC_CR |=CLK_PLL;
					break;

				case STATUS_DISABLE:
					/*Disable The PLL Clock Source*/
					RCC->RCC_CR &=~CLK_PLL;
					break;

				default:
					/* input : status Error*/
					ErrState=Error;
					break;
				}
				break;

				default:
					/* input : Clock source Error */
					ErrState=Error;
					break;
	}
	return ErrState;
}

uint8 MRCC_uint8CheckClkSourceReady(uint8 CLK_RDY)
{
	/*Variable To Store The Return Value That the Clock Source is Ready or Not*/
	uint8 ReturnStatus = CLK_SOURCE_READY;
	/*Variable To Store The Time Out Value Of Waiting*/
	uint32 TimeOut = 0;

	/*Busy Waiting to The Clock Source To Be Ready*/
	while(((RCC->RCC_CR>>CLK_RDY) & 0x01 ) == CLK_SOURCE_NOT_READY)
		// while(GET_BIT(RCC -> RCC_CR, CLK_RDY) == CLK_SOURCE_NOT_READY)
	{
		/*Incrementing the Time Out Value*/
		TimeOut++;
		/*Check If The Time Out Or Not*/
		if (TimeOut == CLK_SOURCE_READY_TIME_OUT)
		{
			/*Return That the Clock Source Not Ready*/
			ReturnStatus = CLK_SOURCE_NOT_READY;
			break;
		}
	}

	return ReturnStatus;
}

res_t MRCC_voidSetClkSource(uint32 sys_clk)
{
	res_t ErrorState=NoError;
	uint32 temp;
	switch (sys_clk)
	{
	case sys_clk_HSI:

		/*Set The HSI To be the System Clock Source By Set SW Bits 0b00*/
		temp = RCC -> RCC_CFGR ;
		temp &= RCC_CFGR_SW_BITS_MASK;
		temp |= sys_clk_HSI;
		RCC -> RCC_CFGR = temp;
		break;

	case sys_clk_HSE:

		/*Set The HSE To be the System Clock Source By Set SW Bits 0b01*/
		temp =RCC -> RCC_CFGR;
		temp &= RCC_CFGR_SW_BITS_MASK;
		temp |= sys_clk_HSE;
		RCC -> RCC_CFGR = temp;
		break;

	case sys_clk_PLL:

		/*Set The PLL To be the System Clock Source By Set SW Bits 0b10*/
		temp =RCC -> RCC_CFGR;
		temp &= RCC_CFGR_SW_BITS_MASK;
		temp |= sys_clk_PLL;
		RCC -> RCC_CFGR = temp;
		break;

	default:

		/* Input : Select system clock Error */
		ErrorState=Error;
		break;
	}
	return ErrorState;
}

res_t MRCC_voidSetPLLConfig(uint8 PLL_SRC,uint8 PLLM,uint16 PLLN,uint8 PLLP,uint8 PLLQ)
{
	res_t ErrorState= NoError ;

	if(PLL_SRC == PLL_SRC_HSI)
	{
		RCC->RCC_PLLCFGR &=PLL_SRC_HSI;
	}
	else if(PLL_SRC == PLL_SRC_HSE)
	{
		RCC->RCC_PLLCFGR |=PLL_SRC_HSE ;
	}
	else
	{
		ErrorState = Error;
	}
	if((PLLM>=2 && PLLM<=62) && (PLLN >= 192 && PLLN <= 432) && (PLLQ >=2 && PLLQ <=15))
	{

		/* masking of PLLM bits and set the PLLM value */
		uint32 temp= RCC->RCC_PLLCFGR;
		temp &= PLLM_MASK;
		temp |= PLLM<<PLLM_startBIT ;
		RCC->RCC_PLLCFGR= temp;

		/*masking of PLLN bits and set the PLLN value */
		temp =RCC->RCC_PLLCFGR;
		temp &= PLLN_MASK;
		temp |= PLLN<<PLLN_startBIT;
		RCC->RCC_PLLCFGR=temp;


		/*Masking of PLLP bits and set the PLLP value */
		temp =RCC->RCC_PLLCFGR;
		temp &= PLLP_MASK;
		temp |= PLLP<<PLLP_startBIT;
		RCC->RCC_PLLCFGR=temp;

		/*Masking of PLLQ bits and set the PLLQ value */
		temp =RCC->RCC_PLLCFGR;
		temp &= PLLQ_MASK;
		temp |= PLLQ<<PLLQ_starBIT;
		RCC->RCC_PLLCFGR=temp;
	}
	else
	{
		ErrorState = Error ;
	}

	return ErrorState;
}

res_t MRCC_voidSetPeripheralStaus(uint8 Bus,uint32 Peripheral,uint8 STATUS)
{
	res_t ErrorState = NoError;
	switch(Bus)
	{
	case Bus_AHB1:
		switch(STATUS)
		{
		case STATUS_ENABLE:
			/* Enable the clock of peripheral on AHB1 Bus */

			RCC->RCC_AHB1ENR |= (1<<Peripheral);
			break;

		case STATUS_DISABLE:

			/* Disable the clock of peripheral on AHB1 Bus */
			RCC->RCC_AHB1ENR &= ~(1<< Peripheral);
			break;

		default:
			/* Input peripheral of AHB1 bus Error */
			ErrorState = Error ;
			break;
		}
		break;

		case Bus_AHB2:
			switch(STATUS)
			{
			case STATUS_ENABLE:
				/* Enable the clock of peripheral on AHB1 Bus */
				RCC->RCC_AHB2ENR |=(1<<Peripheral);
				break;

			case STATUS_DISABLE:
				/* Disable the clock of peripheral on AHB1 Bus */
				RCC->RCC_AHB2ENR &= ~ (1<<Peripheral);
				break;

			default:
				/* Input peripheral of AHB1 bus Error */
				ErrorState = Error ;
				break;
			}

			break;

			case Bus_APB1:
				switch(STATUS)
				{
				case STATUS_ENABLE:

					/* Enable the clock of peripheral on AHB1 Bus */
					RCC->RCC_APB1ENR |= (1<<Peripheral);
					break;
				case STATUS_DISABLE:

					/* Disable the clock of peripheral on AHB1 Bus */
					RCC->RCC_APB1ENR &= ~(1<<Peripheral);
					break;
				default:
					/* Input peripheral of AHB1 bus Error */
					ErrorState = Error ;
					break;
				}

				break;

				case Bus_APB2:
					switch(STATUS)
					{
					case STATUS_ENABLE:
						/* Enable the clock of peripheral on AHB1 Bus */
						RCC->RCC_APB2ENR |= (1<<Peripheral);
						break;
					case STATUS_DISABLE:
						/* Disable the clock of peripheral on AHB1 Bus */
						RCC->RCC_APB2ENR &= ~ (1<<Peripheral);
						break;
					default:
						/* Input peripheral of AHB1 bus Error */
						ErrorState = Error ;
						break;
					}
					break;

					default :
						/* Input bus Error */
						ErrorState = Error ;
						break;
	}
	return ErrorState;
}

res_t MRCC_voidSetBusPrescaler(uint8 Bus, uint32 PRESCALER)
{
	res_t ErrorState=NoError;
	uint32 temp;
	switch(Bus)
	{
	case Bus_AHB1 :
	case Bus_AHB2 :

		temp=RCC->RCC_CFGR;
		temp &=~(0xF<<4);
		temp |=PRESCALER;
		RCC->RCC_CFGR=temp;
		break;

	case Bus_APB1:

		temp=RCC->RCC_CFGR;
		temp &=~(0xF<<10);
		temp |=PRESCALER;
		RCC->RCC_CFGR=temp;
		break;

	case Bus_APB2:

		temp=RCC->RCC_CFGR;
		temp &=~(0xF<<13);
		temp |=PRESCALER;
		RCC->RCC_CFGR=temp;
		break;
	default :
		ErrorState=Error;
		break;
	}
	return ErrorState;
}
void MRCC_voidInit(void)
{

	/*Checking If The Clock Source Configure To be HSE*/
#if CLK_SOURCE == CLK_HSE

	/*Enable The HSE Clock Source*/
	MRCC_voidSetCLKSatus(CLK_HSE, STATUS_ENABLE);

	/*Check That The HSE Clock Source is Ready and Stable*/
	if(MRCC_uint8CheckClkSourceReady(CLK_RDY_HSE) != CLK_SOURCE_NOT_READY)
	{
		/*Selecting That HSE Is the Clock Source of The System*/
		MRCC_voidSetClkSource(sys_clk_HSE);
		/*Disable The HSI Clock Source*/
		MRCC_voidSetCLKSatus(CLK_HSI, STATUS_DISABLE);
		/*Disable The PLL Clock Source*/
		MRCC_voidSetCLKSatus(CLK_PLL, STATUS_DISABLE);
	}


	/*Checking If The Clock Source Configure To be HSI*/
#elif CLK_SOURCE == CLK_HSE

	/*Enable The HSI Clock Source*/
	MRCC_voidSetClkStatus(CLK_HSI, STATUS_ENABLE);

	/*Check That The HSI Clock Source is Ready and Stable*/
	if(MRCC_uint8CheckClkSourceReady(CLK_RDY_HSI) != CLK_SOURCE_NOT_READY)
	{
		/*Selecting That HSI Is the Clock Source of The System*/
		MRCC_voidSetClkSource(sys_clk_HSI);
		/*Disable The HSE Clock Source*/
		MRCC_voidSetClkStatus(CLK_HSE, STATUS_DISABLE);
		/*Disable The PLL Clock Source*/
		MRCC_voidSetClkStatus(CLK_PLL, STATUS_DISABLE);
	}


	/*Checking If The Clock Source Configure To be PLL*/
#elif CLK_SOURCE == PLL
	/*Checking If The Clock Source of PLL Configure To be HSE_SOURCE*/
#if PLL_SOURCE == PLL_SRC_HSE

	/*Enable The HSE Clock Source*/
	MRCC_voidSetClkStatus(CLK_HSE, STATUS_ENABLE);

	/*Check That The HSE Clock Source is Ready and Stable*/
	if(MRCC_uint8CheckClkSourceReady(CLK_RDY_HSE) != CLK_SOURCE_NOT_READY)
	{
		/*Selecting That HSI Is the Clock Source of The System*/
		MRCC_voidSetClkSource(sys_clk_HSI);
		/*Disable The PLL Clock Source To Configure it*/
		MRCC_voidSetClkStatus(CLK_PLL, DISABLE);


		/*Configure HSI Division Factor and PLL Multiplication Factor, Set HSI as PLL Source*/
		MRCC_SetPLLConfiguration(PLL_MULTIPLICATION_FACTOR, HSE, HSE_DIVISION_FACTOR);
		/*Setting AHB , APB1, APB2 Buses Prescaler*/
		MRCC_voidSetBusesPrescalers(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);


		/*Enable The PLL Clock Source*/
		MRCC_voidSetClkStatus(CLK_PLL, ENABLE);

		/*Check That The PLL Clock Source is Ready and Stable*/
		if(MRCC_uint8CheckClkSourceReady(CLK_RDY_PLL) != CLK_SOURCE_NOT_READY)
		{
			/*Selecting That PLL Is the Clock Source of The System*/
			MRCC_voidSetClkSource(sys_clk_PLL);
			/*Disable The HSI Clock Source*/
			MRCC_voidSetClkStatus(CLK_HSI, DISABLE);
		}
	}


	/*Checking If The Clock Source of PLL Configure To be HSI_SOURCE*/
#elif PLL_SOURCE == PLL_SRC_HSI

	/*Enable The HSI Clock Source*/
	MRCC_voidSetClkStatus(HSI, ENABLE);

	/*Check That The HSI Clock Source is Ready and Stable*/
	if(MRCC_uint8CheckClkSourceReady(HSI_RDY) != CLK_SOURCE_NOT_READY)
	{
		/*Selecting That HSI Is the Clock Source of The System*/
		MRCC_voidSetClkSource(HSI);
		/*Disable The PLL Clock Source To Configure it*/
		MRCC_voidSetClkStatus(PLL, DISABLE);


		/*Configure HSI Division Factor and PLL Multiplication Factor, Set HSI as PLL Source*/
		MRCC_SetPLLConfiguration(PLL_MULTIPLICATION_FACTOR, HSI, HSE_DIVISION_FACTOR);
		/*Setting AHB , APB1, APB2 Buses Prescaler*/
		MRCC_voidSetBusesPrescalers(AHB_PRESCALER,APB1_PRESCALER,APB2_PRESCALER);


		/*Enable The PLL Clock Source*/
		MRCC_voidSetClkStatus(PLL, ENABLE);

		/*Check That The PLL Clock Source is Ready and Stable*/
		if(MRCC_uint8CheckClkSourceReady(PLL_RDY) != CLK_SOURCE_NOT_READY)
		{
			/*Selecting That PLL Is the Clock Source of The System*/
			MRCC_voidSetClkSource(PLL);
			/*Disable The HSE Clock Source*/
			MRCC_voidSetClkStatus(HSE, DISABLE);
		}
	}

#else
	/*Printing an Error Message That PLL_SOURCE Configration Error*/
#error"PLL_SOURCE Configuration Error"
#endif
#else
	/*Printing an Error Message That CLOCK_SOURCE Configration Error*/
#error"CLOCK_SOURCE Configuration Error"
#endif

}


