

#ifndef LCD_H_
#define LCD_H_


#define  F_CPU  1000000UL
#include <util/delay.h>
#include "StdTypes.h"
#include "Utils.h"
#include "DIO_Interface.h"

#define  _8_BIT    1
#define  _4_BIT    0

/******************** pin config *************************/

/* choose _8_BIT  _4_BIT**/ 
#define  LCD_MODE  _4_BIT 

#define  RS   PINC6
#define  EN   PINC7

#define  LCD_PORT  PD

#define  D7  PINC5
#define  D6  PINC4
#define  D5  PINC3
#define  D4  PINC2



/*********************************************************/





void LCD_Init(void);

void LCD_WriteNumber(s32 num);
void LCD_WriteString(char*str);
void LCD_WriteChar(u8 ch);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(u8 num);
void LCD_WriteNumber_4D(u16 num);
void LCD_SetCursor(u8 line,u8 cell);
void LCD_CreateChar(u8*pattern ,u8 location);
void LCD_Clear(void);








#endif /* LCD_H_ */