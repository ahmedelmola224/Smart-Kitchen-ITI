#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "UART.h"
static void(*UART_Rx_Fptr)(void)=NULL_PTR;
static void(*UART_Tx_Fptr)(void)=NULL_PTR;

void UART_Init(void)
{
	//Normal speed
	CLR_BIT(UCSRA,U2X);
	//baud rate
	UBRRL=51;
	//8data ,no parity ,1 stop
	//the default
	//enable transmitter &receiver
	SET_BIT(UCSRB,RXEN);
	SET_BIT(UCSRB,TXEN);
}

void UART_Send(u8 data)
{
	while(!READ_BIT(UCSRA,UDRE));
	UDR=data;
}

u8 Uart_Receieve(void)
{
	while(!READ_BIT(UCSRA,RXC));
	return UDR;
}

void UART_SendNoBlock(u8 data)
{
	UDR=data;
}

u8 UART_ReceieveNoBlock()
{
	return UDR;
}

u8 Uart_ReceievePeriodic(u8* pdata)
{
	if(READ_BIT(UCSRA,RXC))
	{
		*pdata=UDR;
		return 1;
	}
	return 0;
	
}


void UART_Rx_InterruptEnable(void)
{
	SET_BIT(UCSRB,RXCIE);
}

void UART_Rx_InterruptDisable(void)
{
	CLR_BIT(UCSRB,RXCIE);
}

void UART_Tx_InterruptEnable(void)
{
	SET_BIT(UCSRB,TXCIE);
}

void UART_Tx_InterruptDisable(void)
{
	CLR_BIT(UCSRB,TXCIE);
}

void UART_Rx_SetCallBack(void(*LocalFptr)(void))
{
	UART_Rx_Fptr=LocalFptr;
}
void UART_Tx_SetCallBack(void(*LocalFptr)(void))
{
	UART_Tx_Fptr=LocalFptr;
}

ISR(UART_RX_vect)
{
	if(UART_Rx_Fptr!=NULL_PTR)
	{
		UART_Rx_Fptr();
	}
}

ISR(UART_TX_vect)
{
	if(UART_Tx_Fptr!=NULL_PTR)
	{
		UART_Tx_Fptr();
	}
}