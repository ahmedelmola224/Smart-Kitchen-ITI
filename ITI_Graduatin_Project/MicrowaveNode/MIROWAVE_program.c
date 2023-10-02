#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "SSD.h"
#include "MOTOR_interface.h"
#include "MICROWAVE_interface.h"
#include "MICROWAVE_private.h"
#define  F_CPU  1000000UL
#include <util/delay.h>

static volatile u8 MW_u8State = MICROWAVE_NOT_WORKING;
static u8 MW_Min_Sec[2]={0};
static volatile u8 rec_Frame[3]={0};
static volatile u8 MW_u8StopFlag=1;

void MICCROWAVE_voidRecieveInt()
{
	static u8 counter=0;
	rec_Frame[counter]=SPI_ReceieveNoBlock();
	SPI_SendNoBlock(MW_u8State);
	MW_u8StopFlag=rec_Frame[0];
	counter++;
	if(counter==3)
	{
		counter=0;
		if(MW_u8State==MICROWAVE_NOT_WORKING)
		{
			MoveData();
		}
	}
	
}
void MICROWAVE_voidInit(void)
{
	DIO_Init();
	MOTOR_Init();
	SPI_Init();
	SPI_SetCallBack(MICCROWAVE_voidRecieveInt);
	SPI_InterruptEnable();
	__asm__  __volatile__ ("sei" ::);
}

void MoveData()
{
	if(MW_u8StopFlag)
	{
		MW_Min_Sec[0]=rec_Frame[1];
		MW_Min_Sec[1]=rec_Frame[2];
		MW_u8State=MICROWAVE_WORKING;
	}
}

void MICROWAVE_voidRunnable(void)
{
	s32 i,j;
	if(MW_u8State == MICROWAVE_WORKING)
	{
		
		while(DIO_ReadPin(PINA1)==HIGH)
		{
			SSD_voidDisplay(MW_Min_Sec[0],MW_Min_Sec[1]);
		}
		MOTOR_Cw(M1);
		for(i=MW_Min_Sec[0];i>=0;)
		{
			MOTOR_Cw(M1);			
			for(j=0;j<100;j++)
			{
				
				SSD_voidDisplay(i,MW_Min_Sec[1]);
				while(DIO_ReadPin(PINA1)==HIGH)
				{
					MOTOR_Stop(M1);
					SSD_voidDisplay(i,MW_Min_Sec[1]);
				}
			}
				if(MW_Min_Sec[1]==0)
				{
					if(i>0)
					{
						MW_Min_Sec[1]=60;	
					}
					
					else if (i==0)
					{
						MOTOR_Stop(M1);
						while(DIO_ReadPin(PINA1)==LOW)
						{
							
							DIO_WritePin(PINA0,HIGH);
							for(int k=0;k<2000&&DIO_ReadPin(PINA1)==LOW;k++)
							{
								SSD_voidDisplay(0,MW_Min_Sec[1]);
								_delay_ms(1);
								
							}
							DIO_WritePin(PINA0,LOW);
							for(int k=0;k<2000&&DIO_ReadPin(PINA1)==LOW;k++)
							{
								SSD_voidDisplay(0,MW_Min_Sec[1]);
								_delay_ms(1);
							}
						}
						MW_u8State=MICROWAVE_NOT_WORKING;
					}
					i--;
				}
				if(MW_u8StopFlag==0)
				{
					MW_u8State = MICROWAVE_NOT_WORKING;
					MW_u8StopFlag=1;
					break;
				}
			MW_Min_Sec[1]--;
		
		}
		
	}
	else if(MW_u8State == MICROWAVE_NOT_WORKING)
	{
		DIO_WritePin(PINA0,LOW);
		MOTOR_Stop(M1);
		SSD_voidDisplay(0,0);
	}
	
	
}