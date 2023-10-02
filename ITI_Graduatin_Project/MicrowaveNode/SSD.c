#include "StdTypes.h"
#include "DIO_interface.h"
#include "SSD.h"
#define  F_CPU  1000000UL
#include <util/delay.h>
static int arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
void SSD_voidDisplay(u8 mins,u8 sec)
{
	 	
	 	DIO_WritePin(SSD_PIN+1,HIGH);
		 DIO_WritePin(SSD_PIN+2,HIGH);
		 DIO_WritePin(SSD_PIN+3,HIGH);
	 	DIO_WritePort(SSD_PORT,~arr[mins/10]);
		 DIO_WritePin(SSD_PIN,LOW);
	 	_delay_ms(2);
	 	
	 	DIO_WritePin(SSD_PIN,HIGH);
		DIO_WritePin(SSD_PIN+2,HIGH);
		DIO_WritePin(SSD_PIN+3,HIGH);
	 	DIO_WritePort(SSD_PORT,~arr[mins%10]);
		 DIO_WritePin(SSD_PIN+1,LOW);
	    _delay_ms(2);	
		
		 DIO_WritePin(SSD_PIN,HIGH);
		 DIO_WritePin(SSD_PIN+1,HIGH);
		 DIO_WritePin(SSD_PIN+3,HIGH);
		 DIO_WritePort(SSD_PORT,~arr[sec/10]);
		  DIO_WritePin(SSD_PIN+2,LOW);
		 _delay_ms(2);
		 
		 DIO_WritePin(SSD_PIN+1,HIGH);
		 DIO_WritePin(SSD_PIN,HIGH);
		 DIO_WritePin(SSD_PIN+2,HIGH);
		 DIO_WritePort(SSD_PORT,~arr[sec%10]);
		 DIO_WritePin(SSD_PIN+3,LOW);
		 _delay_ms(2);
}

