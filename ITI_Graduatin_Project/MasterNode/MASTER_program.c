#include "StdTypes.h"
#include "Utils.h"
#include "DIO_interface.h"
#include "SPI.h"
#include "KeyPad_interface.h"
#include "LCD.h"
#include "TWI.h"
#include "UART.h"
#include "EEPROM.h"
#include "MASTER_interface.h"
#include "MASTER_private.h"

static u8 MASTER_u8ActualPass[20];
static u8 MASTER_u8State =MASTER_CHECK_PASS;

void MASTER_rx()
{
	u8 rec =UART_ReceieveNoBlock();
	if(rec==100)
	{
		MASTER_u8State=MASTER_CHECK_PASS;
	}
}
void MASTER_voidInit(void)
{
	/*initialization of the required Modules */
	DIO_Init();
	LCD_Init();
	SPI_Init();
	UART_Init();
	TWI_Init(1);
	KEYPAD_Init();
	/*Reading the password from eeprom*/
	EEPROM_ReadString(MASTER_PASSWORD_LOCATION,MASTER_u8ActualPass);
}

void MASTER_voidRunnable(void)
{
	
	switch(MASTER_u8State)
	{
		case MASTER_CHECK_PASS:
		MASTER_voidGetPassState();
		break;
		case MASTER_CHANGE_MENU:
		MASTER_voidChangeMenuState();
		break;
		case MASTER_GET_MENU:
		MASTER_voidShowMenuState();
		break;
		case MASTER_ORDER_STOVE:
		MASTER_voidSendStoveOrderState();
		break;
		case MASTER_ORDER_MICROWAVE:
		MASTER_voidSendMicrowaveOrderState();
		break;
		case MASTER_ORDER_WASHINGMACHINE:
		WM_voidGetState();
		break;
		case MASTER_ORDER_SYSTEMSTATE:
		MASTER_voidSendSystemState();
		break;
		
	}
}

static void MASTER_voidGetState(u8*temp,u8* pressure)
{
	UART_Send(100);
	*temp=Uart_Receieve();
	*pressure=Uart_Receieve();
}

static void MASTER_voidSendSystemState(void)
{
	u8 temp=0,pressure=0,btn;
	MASTER_voidGetState(&temp,&pressure);
	LCD_Clear();
	LCD_WriteString("TEMP: ");
	LCD_WriteNumber(temp);
	LCD_SetCursor(1,0);
	LCD_WriteString("Pressure: ");
	LCD_WriteNumber(pressure);
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			MASTER_u8State=MASTER_GET_MENU;
			break;
		}
	}
	
}

static void WM_voidGetState(void)
{
	u8 rec;
	DIO_WritePin(PIND5,LOW);
	DIO_WritePin(PIND7,HIGH);
	DIO_WritePin(PIND6,HIGH);
	rec = SPI_SendReceieve(100);
	_delay_ms(2);
	rec = SPI_SendReceieve(100);
	DIO_WritePin(PIND5,HIGH);
	if(rec==WM_NOT_WORKING)
	{
		MASTER_voidSendWashingmachineOrderState();
	}
	else if(rec==WM_WORKING)
	{
		MASTER_voidSendWashingmachineStop();
	}
}
static void MASTER_voidSendWashingmachineStop()
{
	u8 btn,rec;
	LCD_Clear();
	LCD_WriteString("1.Stop");
	LCD_SetCursor(1,0);
	LCD_WriteString("2.Get Back");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==MW_GETBACK)
			{
				break;
			}
			else if(btn==MW_STOP)
			{
				DIO_WritePin(PIND5,LOW);
				DIO_WritePin(PIND7,HIGH);
				DIO_WritePin(PIND6,HIGH);
				rec=SPI_SendReceieve(200);
				DIO_WritePin(PIND5,HIGH);
				break;
			}
		}
	}
	
	
	
MASTER_u8State=MASTER_GET_MENU;
}

static void MASTER_voidSendWashingmachineOrderState(void)
{
	u8 btn,color=0,receive,water;
	LCD_Clear();
	LCD_WriteString("Clothes Color:");
	LCD_SetCursor(1,0);
	LCD_WriteString("1.Black");
	LCD_WriteString("  2.White");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==WHITE||btn==BLACK)
			{
				color=btn;
				break;
			}
		}
	}
	
	LCD_Clear();
	LCD_WriteString("Water:");
	LCD_SetCursor(1,0);
	LCD_WriteString("1.Hot");
	LCD_WriteString("    2.Cold");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==(HOT-2)||btn==(COLD-2))
			{
				water=btn+2;
				break;
			}
		}
	}
	//spi sending
		DIO_WritePin(PIND5,LOW);
		DIO_WritePin(PIND7,HIGH);
		DIO_WritePin(PIND6,HIGH);
		receive = SPI_SendReceieve(color);
		_delay_ms(2);
		receive = SPI_SendReceieve(water);
		DIO_WritePin(PIND5,HIGH);
	MASTER_u8State=MASTER_GET_MENU;
}

static void MASTER_voidSendMicrowaveOrderState(void)
{
	u8 btn,rec,choice=0,min=0,sec=0,counter=0;
	LCD_Clear();
	LCD_WriteString("1.Set Time");
	LCD_SetCursor(1,0);
	LCD_WriteString("2.Stop");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn !=NO_KEY)
		{
			if(btn == MICROWAVE_SET_TIME)
			{
				choice=1;
				LCD_Clear();
				LCD_WriteString("Time:00:00");
				while(1)
				{
					btn =KEYPAD_GetKey();
					if(btn >= '0'&&btn <= '9')
					{
						if(counter==0)
						{
							min=(btn-'0') * 10;
							LCD_SetCursor(0,5);
							LCD_WriteNumber(min);
						}
						else if(counter==1)
						{
							min=min+(btn-'0');
							LCD_SetCursor(0,6);
							LCD_WriteNumber((btn-'0'));
						}
						else if(counter==2)
						{
							sec=(btn-'0') * 10;
							LCD_SetCursor(0,8);
							LCD_WriteNumber(sec);
						}
						else if(counter==3)
						{
							sec=sec+(btn-'0');
							LCD_SetCursor(0,8);
							LCD_WriteNumber((btn-'0'));
							break;
						}
						counter++;
					}
				}
				break;
			}
			else if(btn == MICROWAVE_STOP)
			{
				choice=MICROWAVE_STOP - '2';
				break;
			}
		}
	}
	//spi sending
	DIO_WritePin(PIND5,HIGH);
	DIO_WritePin(PIND6,HIGH);
	DIO_WritePin(PIND7,LOW);
	rec=SPI_SendReceieve(choice);
	_delay_ms(1);
	rec=SPI_SendReceieve(min);
	_delay_ms(1);
	rec=SPI_SendReceieve(sec);
	DIO_WritePin(PIND7,HIGH);
	if(rec==1&&choice==1)
	{
		LCD_Clear();
		LCD_WriteString("Can't set time !");
		_delay_ms(2000);
	}
	//menu state
	MASTER_u8State=MASTER_GET_MENU;
}

static void MASTER_voidSendStoveOrderState(void)
{
	u8 btn,choice=0,receive;
		LCD_Clear();
		LCD_WriteString("1.F1");
		LCD_WriteString(" 2.F2");
		LCD_WriteString(" 3.F3");
		LCD_SetCursor(1,0);
		LCD_WriteString("4.F4");
		LCD_WriteString("      5.F5");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if((btn==FLAME1||btn==FLAME2||btn==FLAME3||btn==FLAME4||btn==FLAME5)&&choice==0)
			{
				choice=(btn-'0')*2-1;
				LCD_Clear();
				LCD_WriteString("Flame");
				LCD_WriteChar(btn);
				LCD_SetCursor(1,0);
				LCD_WriteString("1.ON");
				LCD_WriteString("     2.OFF");
			}
			else if((btn==FLMAE_ON||btn==FLAME_OFF)&&choice!=0)
			{
				MASTER_u8State=MASTER_GET_MENU;
				choice=choice+(btn-'1');
				LCD_Clear();
				break;
			}
			
		}
	}
	DIO_WritePin(PIND5,HIGH);
	DIO_WritePin(PIND7,HIGH);
	DIO_WritePin(PIND6,LOW);
	receive=SPI_SendReceieve(choice);
	DIO_WritePin(PIND6,HIGH);
}

static void MASTER_voidShowMenuState(void)
{
	u8 btn;
	u16 c=0;
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString("1.Stove");
	LCD_SetCursor(0,8);
	LCD_WriteString("2.MW");
	LCD_SetCursor(1,0);
	LCD_WriteString("3.WM");
	LCD_SetCursor(1,8);
	LCD_WriteString("4.Ss");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn==MASTER_STOVE)
			{
				MASTER_u8State=MASTER_ORDER_STOVE;
				break;
			}
			else if(btn == MASTER_MICROWAVE)
			{
				MASTER_u8State = MASTER_ORDER_MICROWAVE;
				break;
			}
			else if (btn ==MASTER_WASHINGMACHINE)
			{
				MASTER_u8State = MASTER_ORDER_WASHINGMACHINE;
				break;
			}
			else if(btn ==MASTER_SYSTEMSTATE)
			{
				MASTER_u8State = MASTER_ORDER_SYSTEMSTATE;
				break;
			}
		}
		else
		{
			c++;
			_delay_ms(1);
			if(c==5000)
			{
				LCD_Clear();
				LCD_SetCursor(0,4);
				LCD_WriteString("12-9-2023");
				LCD_SetCursor(1,4);
				LCD_WriteString("5:30 PM");
				while(1)
				{
					btn =KEYPAD_GetKey();
					if(btn!=NO_KEY)
					{
						break;
					}
				}
				break;
			}
		}
	}
	
}

static void MASTER_voidChangeMenuState(void)
{
	u8 MASTER_u8RecPass[20];
	u8 btn;
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString("1.Change pass");
	LCD_SetCursor(1,0);
	LCD_WriteString("2.Menu");
	while(1)
	{
		btn =KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn == MASTER_CHANGE_PASS)
			{
				LCD_Clear();
				LCD_SetCursor(0,0);
				LCD_WriteString("New Pass: ");
				MATSER_voidReceievePassword(MASTER_u8RecPass);
				MASTER_CopyPassword(MASTER_u8RecPass,MASTER_u8ActualPass);
				EEPROM_WriteString(MASTER_PASSWORD_LOCATION,MASTER_u8ActualPass);
				LCD_Clear();
				LCD_WriteString("Pass Changed");
				_delay_ms(2000);
				MASTER_u8State--;
				break;
			}
			else if(btn ==MASTER_SHOW_MENU)
			{
				MASTER_u8State++;
				break;
			}
		}
		
	}
	
}
static void MASTER_voidGetPassState(void)
{
	u8 MASTER_u8RecPass[20];
	LCD_Clear();
	LCD_SetCursor(0,0);
	LCD_WriteString("Welcome");
	_delay_ms(500);
	LCD_WriteChar('.');
	_delay_ms(500);
	LCD_WriteChar('.');
	_delay_ms(500);
	LCD_WriteChar('.');
	_delay_ms(500);
	LCD_Clear();
	LCD_WriteString("Password: ");
	MATSER_voidReceievePassword(MASTER_u8RecPass);
	if(MASTER_CheckPassword(MASTER_u8RecPass,MASTER_u8ActualPass)== MASTER_CORRECT_PASS)
	{
		MASTER_u8State++;
	}
	else
	{
		LCD_Clear();
		LCD_WriteString("Wrong Password");
		_delay_ms(2000);
	}
	
}


static void MATSER_voidReceievePassword(u8*str)
{
	u8 i=0,btn;
	while(1)
	{
		btn=KEYPAD_GetKey();
		if(btn!=NO_KEY)
		{
			if(btn=='=')
			{
				str[i]=0;
				break;;
			}
			str[i]=btn;
			i++;
			LCD_WriteChar('*');
		}
	}
}

static u8 MASTER_CheckPassword(u8* str1,u8* str2)
{
	for(u8 i=0;str1[i]&&str2[i];i++)
	{
		if(str1[i]!=str2[i])
		{
			return MASTER_WRONG_PASS;
		}
	}
	return MASTER_CORRECT_PASS;
}

static void MASTER_CopyPassword(u8*str1,u8*str2)
{
	u8 i=0;
	str2[i]=str1[i];
	while(str2[i])
	{
		i++;
		str2[i]=str1[i];
	}
}
