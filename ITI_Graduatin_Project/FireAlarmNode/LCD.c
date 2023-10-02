
#include "LCD.h"

#if LCD_MODE==_8_BIT

static void LCD_WriteCommand(u8 command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePort(LCD_PORT,command);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}
static void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePort(LCD_PORT,data);
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	
	LCD_WriteCommand(0x38);//2 lines, 8 bit mode
	LCD_WriteCommand(0x0c);//0x0e,0x0f
	LCD_WriteCommand(0x01);//clear
	_delay_ms(1);
	LCD_WriteCommand(0x06);//increment DDRAM address
	
}

/****************************************4 BIT **************************************/
#elif LCD_MODE==_4_BIT
static void LCD_WriteCommand(u8 command)
{
	DIO_WritePin(RS,LOW);
	DIO_WritePin(D7,READ_BIT(command,7));
	DIO_WritePin(D6,READ_BIT(command,6));
	DIO_WritePin(D5,READ_BIT(command,5));
	DIO_WritePin(D4,READ_BIT(command,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(command,3));
	DIO_WritePin(D6,READ_BIT(command,2));
	DIO_WritePin(D5,READ_BIT(command,1));
	DIO_WritePin(D4,READ_BIT(command,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	
	
}
static void LCD_WriteData(u8 data)
{
	DIO_WritePin(RS,HIGH);
	DIO_WritePin(D7,READ_BIT(data,7));
	DIO_WritePin(D6,READ_BIT(data,6));
	DIO_WritePin(D5,READ_BIT(data,5));
	DIO_WritePin(D4,READ_BIT(data,4));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
	DIO_WritePin(D7,READ_BIT(data,3));
	DIO_WritePin(D6,READ_BIT(data,2));
	DIO_WritePin(D5,READ_BIT(data,1));
	DIO_WritePin(D4,READ_BIT(data,0));
	DIO_WritePin(EN,HIGH);
	_delay_ms(1);
	DIO_WritePin(EN,LOW);
	_delay_ms(1);
}


void LCD_Init(void)
{
	_delay_ms(50);
	LCD_WriteCommand(0x02);
	LCD_WriteCommand(0x28);//2 lines, 4 bit mode
	LCD_WriteCommand(0x0C);//0x0e,0x0f
	LCD_WriteCommand(0x01);//clear
	_delay_ms(1);
	LCD_WriteCommand(0x06);//increment DDRAM address
	
}
#endif

/***************************************************************************/

void LCD_WriteChar(u8 ch)
{
	LCD_WriteData(ch);
}


void LCD_WriteString(char*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		LCD_WriteChar(str[i]);
	}
	
}

void LCD_WriteNumber(s32 num)   //-2503
{
	u8 rem,i=0,str[16];
	s8 j;
	if (num==0)
	{
		LCD_WriteChar('0');
		return;
	}
	if (num<0)
	{
		num=num*(-1);
		LCD_WriteChar('-');
	}
	
	while(num)
	{
		rem=num%10;
		rem=rem+'0';
		str[i]=rem;
		i++;
		num=num/10;	
	}
	
	for (j=i-1;j>=0;j--)
	{
		LCD_WriteChar(str[j]);
	}

}

void LCD_Clear(void)
{
	LCD_WriteCommand(0x01);//clear
	_delay_ms(1);
}


void LCD_SetCursor(u8 line,u8 cell)
{
		if (line==0)
		{
			LCD_WriteCommand(0x80+cell);
		}
		else if (line==1)
		{
			LCD_WriteCommand(0x80+0x40+cell);
		}
}

void LCD_WriteNumber_4D(u16 num)
{
	LCD_WriteChar(((num%100000)/10000)+'0');
	LCD_WriteChar(((num%10000)/1000)+'0');
	LCD_WriteChar(((num%1000)/100)+'0');
	LCD_WriteChar(((num%100)/10)+'0');
	LCD_WriteChar(((num%10)/1)+'0');
}

void LCD_WriteBinary(u8 num)
{
	s8 i;
	for (i=7;i>=0;i--)
	{
		LCD_WriteChar(((num>>i)&1)+'0');
	}

}

void LCD_CreateChar(u8*pattern ,u8 location)
{
	u8 i=0;
	LCD_WriteCommand(0x40+(location*8)); //Send the Address of CGRAM
	for(i=0;i<8;i++)
	{
		LCD_WriteData(pattern[i]); //Pass the bytes of pattern on LCD
	}
	LCD_WriteCommand(0x80);
}


void LCD_WriteHex(u8 num) //0x35
{
	u8 HN=num>>4;
	u8 LN=num&0x0f;
	if (HN<10)
	{
		LCD_WriteChar(HN+'0');
	}
	else
	{
		LCD_WriteChar(HN-10+'A');
	}
	if (LN<10)
	{
		LCD_WriteChar(LN+'0');
	}
	else
	{
		LCD_WriteChar(LN-10+'A');
	}
};