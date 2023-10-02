#include "StdTypes.h"
#define KEYPAD_PROG
#include "KeyPad_interface.h"
#include "KeyPad_cfg.h"


void KEYPAD_Init(void)
{
	u8 i;
	for(i=0;i<ROWS;i++)
	{
		DIO_WritePin(KeyPadOutputPin[i],HIGH);
	}
}
u8 KEYPAD_GetKey(void)
{
	u8 r,c,key=NO_KEY;
	for(r=0;r<ROWS;r++)
	{
		DIO_WritePin(KeyPadOutputPin[r],LOW);
		for(c=0;c<COLS;c++)
		{
			if(DIO_ReadPin(KeyPadInputPin[c])==LOW)
			{
				key=KeysArray[r][c];
				while(DIO_ReadPin(KeyPadInputPin[c])==LOW);
			}
			
		}
		DIO_WritePin(KeyPadOutputPin[r],HIGH);
	}
	return key;
	
}