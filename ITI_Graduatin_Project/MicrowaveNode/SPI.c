#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "SPI.h"

static void (*SPI_Fptr)(void)=NULL_PTR;

void SPI_Init(void)
{
	
	//clock by default f/4
	
	if(SPIMODE==MASTER)
	{
		SET_BIT(SPCR,MSTR);
	}
	else if(SPIMODE==SLAVE)
	{
		CLR_BIT(SPCR,MSTR);
		
	}
	//spi enable
	SET_BIT(SPCR,SPE);
}


u8 SPI_SendReceieve(u8 data)
{
	SPDR=data;
	while(!READ_BIT(SPSR,SPIF));
	return SPDR;
}

void SPI_SendNoBlock(u8 data)
{
	SPDR=data;
}

u8 SPI_ReceieveNoBlock(void)
{
	return SPDR;
}


u8 SPI_ReceievePeriodic(u8 *pdata)
{
	if(READ_BIT(SPSR,SPIF))
	{
		*pdata=SPDR;
		return 1;
	}
	return 0;
}

void SPI_InterruptEnable(void)
{
	SET_BIT(SPCR,SPIE);
}

void SPI_InterruptDisable(void)
{
	CLR_BIT(SPCR,SPIE);
}

void SPI_SetCallBack(void(*LocalFptr)(void))
{
	SPI_Fptr=LocalFptr;
}

ISR(SPI_vect)
{
	if(SPI_Fptr!=NULL_PTR)
	{
		SPI_Fptr();
	}
}