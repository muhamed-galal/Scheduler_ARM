/*
 * FLASH.h
 *
 *  Created on: Jun 8, 2023
 *      Author: Muham
 */

#ifndef FLASH_FLASH_H_
#define FLASH_FLASH_H_

#include "../../Common/STD_TYPES.h"
#include "../../Common/util.h"

/**************************************************************************************************************************************
* MACRO		: 	To Configure 																						         		  *
* options	:	Start sector from  sector 1 to sector 5																												  *
**************************************************************************************************************************************/
#define START_SECTOR													3
/**************************************************************************************************************************************
* MACRO		: 	To Configure 																						         		  *
* options	:	End sector from  sector 1 to sector 5																														  *
**************************************************************************************************************************************/
#define END_SECTOR														5

/*************************************************************************************************************************************/
/***************************************************** Functions Prototypes **********************************************************/
/*************************************************************************************************************************************/
/**************************************************************************************************************************************
* Function Name		: MFLASH_voidAreaErase																		                      *
* Parameters (in)	: None																						                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Erase the Application Area								                                          *
**************************************************************************************************************************************/
void MFLASH_voidAreaErase(void);
/**************************************************************************************************************************************
* Function Name		: MFLASH_voidSectorErase														    			                  *
* Parameters (in)	: uint8 SectorNum 									                            			                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To Erase sector of flash memory main area								                              *
**************************************************************************************************************************************/
void MFLASH_voidSectorErase(uint8 SectorNum );
/**************************************************************************************************************************************
* Function Name		: MFLASH_voidWrite																				                  *
* Parameters (in)	: uint32 Address, uint16 * Data, uint8 Length												                      *
* Parameters (out)	: None																						                      *
* Return value		: None																						                      *
* Description		: Function To write data at flash memory address									                              *
**************************************************************************************************************************************/
void MFLASH_voidWrite(uint32 Address, uint16 * Data, uint8 Length);


#endif /* FLASH_FLASH_H_ */