/*
 * EEPROM.c
 *
 * Created: 9/3/2023 4:02:57 PM
 *  Author: ahmed
 */ 
#define F_CPU 1000000UL
#include <util/delay.h>

#include "StdTypes.h"
#include "Utils.h"
#include "TWI.h"
#include "EEPROM.h"

static void EEPROM_WriteData(u16 Copy_u16Address,u8 Copy_u8Data)
{
	TWI_Start();
	TWI_WriteAdress(EEPROM_FIXED_SEQ|(A2_pin<<2)|(Copy_u16Address>>8),TWI_WRITE);
	TWI_WriteData((u8)Copy_u16Address);
	TWI_WriteData(Copy_u8Data);
	TWI_Stop();
	_delay_ms(10);
}

static u8 EEPROM_ReadData(u16 Copy_u16Address)
{
	u8 LOC_u8Data;
	TWI_Start();
	TWI_WriteAdress(EEPROM_FIXED_SEQ|(A2_pin<<2)|(Copy_u16Address>>8),TWI_WRITE);
	TWI_WriteData((u8)Copy_u16Address);
	TWI_Start();
	TWI_WriteAdress(EEPROM_FIXED_SEQ|(A2_pin<<2)|(Copy_u16Address>>8),TWI_READ);
	LOC_u8Data=TWI_ReadData();
	TWI_Stop();
	return LOC_u8Data;
}

void EEPROM_WriteString(u16 address,u8*str)
{
	u8 i=0;
	while(str[i])
	{
		EEPROM_WriteData(address+i,str[i]);
		i++;
	}
	EEPROM_WriteData(address+i,str[i]);
}


void EEPROM_ReadString(u16 address,u8*str)
{
	u8 i=0;
	str[i]=EEPROM_ReadData(address+i);
	for(;str[i];)
	{
		i++;
		str[i] = EEPROM_ReadData(address+i);
	}
}