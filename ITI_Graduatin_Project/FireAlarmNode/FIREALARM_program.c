#include "MemoryMap.h"
#include "DIO_interface.h"
#include "ADC_interface.h"
#include "UART.h"
#include "Sensors.h"
#include "FIREALARM_inteface.h"
#include "FIREALARM_private.h"

volatile u8 temp;
volatile u16 pressure;
void FIREALARM_rx(void)
{
	u8 rec =UART_ReceieveNoBlock();
	if(rec==100)
	{
		UART_Send(temp);
		UART_Send(pressure);
	}
	
}
void FIREALARM_voidInit(void)
{
	DIO_Init();
	LCD_Init();
	ADC_Init(VREF_AREF,ADC_SCALER_64);
	UART_Init();
	UART_Rx_SetCallBack(FIREALARM_rx);
	UART_Rx_InterruptEnable();
	sei();
}

void FIREALARM_voidRunnale(void)
{
	LCD_Clear();
	cli();
	pressure=PRESSURE_Read();
	temp=TEMP_Read();
	temp=temp/2;
	pressure=pressure/10;
	sei();
	//fine state
	if(temp<45&&pressure<40)
	{
		DIO_WritePin(PINB0,HIGH);
		DIO_WritePin(PINB1,LOW);
		DIO_WritePin(PINB2,LOW);
	}
	else if(temp>48||pressure>43)
	{
		DIO_WritePin(PINB0,LOW);
		DIO_WritePin(PINB1,HIGH);
		DIO_WritePin(PINB2,HIGH);
		
	}
}
