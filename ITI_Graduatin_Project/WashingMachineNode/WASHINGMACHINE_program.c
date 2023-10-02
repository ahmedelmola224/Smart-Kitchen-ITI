#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "SERVO.h"
#include "SSD.h"
#include "MOTOR_interface.h"
#include "WASHINGMACHINE_interface.h"
#include "WASHINGMACHINE_private.h"
#define  F_CPU  1000000UL
#include <util/delay.h>


static u8 MW_Min_Sec[2]={0,59}; 
volatile u8 WM_u8State =WM_NOT_WORKING;
volatile u8 WM_u8Stop=0;
volatile u8 WM_u8Mode[2];

static void WM_Interrupt()
{
	
	static u8 counter=0;
	u8 rec=SPI_ReceieveNoBlock();
	if(rec==100)
	{
		SPI_SendNoBlock(WM_u8State);
	}
	else if(rec==200)
	{
		WM_u8Stop=1;
	}
	else
	{
		WM_u8Mode[counter]=rec;
		counter++;
		if(counter==2)
		{
			WM_u8State=WM_WORKING;
			counter=0;
		}
	}
	
}

static void WASHINGMCHINE_voidStopMode()
{
	DIO_WritePin(PINA0,LOW);
	DIO_WritePin(PINA1,LOW);
	DIO_WritePin(PINA2,LOW);
	DIO_WritePin(PINA3,LOW);

}

static void WASHINGMACHINE_voidSetMode(u8 Mode)
{
	switch(Mode)
	{
		case BLACK_CLOTHES_MODE:
		DIO_WritePin(PINA0,HIGH);
		break;
		case WHITE_CLOTHES_MODE:
		DIO_WritePin(PINA1,HIGH);
		break;
		case HOT_WATER_MODE:
		DIO_WritePin(PINA2,HIGH);
		break;
		case COLD_WATER_MODE:
		DIO_WritePin(PINA3,HIGH);
		break;
		default:
		break;
	}
}

void WASHINGMACHINE_voidInit(void)
{
	DIO_Init();
	SPI_Init();
	Timer1_Init(TIMER1_FASTPWM_ICR_TOP_MODE,TIMER1_SCALER_1);
	SERVO_Init();
	SPI_SetCallBack(WM_Interrupt);
	SPI_InterruptEnable();
	__asm__  __volatile__ ("sei" ::);
}

void WASHINGMACHINE_voidRunnable(void)
{
	if(WM_u8State==WM_WORKING)
	{
		s32 i,j,c=0,angle=0;
		WASHINGMACHINE_voidSetMode(WM_u8Mode[0]);
		WASHINGMACHINE_voidSetMode(WM_u8Mode[1]);
		MOTOR_Cw(M1);
		_delay_ms(1000);
		MOTOR_Stop(M1);
		SERVO_Angle(angle);
			for(i=MW_Min_Sec[0];i>=0;)
			{
				for(j=0;j<100;j++)
				{
					SSD_voidDisplay(i,MW_Min_Sec[1]);
				}
				if(MW_Min_Sec[1]==0)
				{
					if(i>0)
					{
						MW_Min_Sec[1]=60;
					}
					
					else if (i==0)
					{
						MW_Min_Sec[1]=60;
						WM_u8State=WM_NOT_WORKING;
						SERVO_Angle(0);
					}
					i--;
				}
				if(WM_u8Stop==1)
				{
					WM_u8State = WM_NOT_WORKING;
					WM_u8Stop=0;
					SERVO_Angle(0);
					break;
				}
				if(c==4)
				{
					angle=(angle==0)?(180):(0);
					SERVO_Angle(angle);
					c=0;
				}
				MW_Min_Sec[1]--;	
				c++;
		}
		
	}
	else if(WM_u8State==WM_NOT_WORKING)
	{
		MOTOR_Stop(M1);
		 WASHINGMCHINE_voidStopMode();
		 SSD_voidDisplay(0,0);
	}
}
