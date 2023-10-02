/*
 * STOVE_PROG.h
 *
 * Created: 9/5/2022 12:03:01 AM
 *  Author: Basel Ashraf
 */ 

#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "STOVE_interface.h"
#include "STOVE_private.h"


static u8 FLAME_State =FLAMES_DEFAULT;
static void STOVE_FLAMEOnOff(u8 FLAME_state)
{
	
	   switch(FLAME_state)
	 	 {
	 		 case FLAME1_ON:
	 		 DIO_WritePin(PINC0,HIGH);break;
	 		 case FLAME1_OFF:
	 		 DIO_WritePin(PINC0,LOW);break;
	 		 case FLAME2_ON:
	 		 DIO_WritePin(PINC1,HIGH);break;
	 		 case FLAME2_OFF:
	 		 DIO_WritePin(PINC1,LOW);break;
	 		 case FLAME3_ON:
	 		 DIO_WritePin(PINC2,HIGH);break;
	 		 case FLAME3_OFF:
	 		 DIO_WritePin(PINC2,LOW);break;
	 		 case FLAME4_ON:
	 		 DIO_WritePin(PINC3,HIGH);break;
	 		 case FLAME4_OFF:
	 		 DIO_WritePin(PINC3,LOW);break;
	 		 case FLAME5_ON:
	 		 DIO_WritePin(PINC4,HIGH);break;
	 		 case FLAME5_OFF:
	 		 DIO_WritePin(PINC4,LOW);break;
	 		 default:break;
	 	 }
		  FLAME_State=FLAMES_DEFAULT;
}

 void STOVE_Init(void)
 {
	 DIO_Init();
	 SPI_Init(); 
 }
 void STOVE_Runnable()
 {
	 FLAME_State=SPI_SendReceieve(FLAMES_DEFAULT);
	STOVE_FLAMEOnOff(FLAME_State);
 }
 
 
