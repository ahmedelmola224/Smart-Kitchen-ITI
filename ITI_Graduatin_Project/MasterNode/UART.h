


#ifndef UART_H_
#define UART_H_

void UART_Init(void);
void UART_Send(u8 data);
u8 Uart_Receieve(void);
u8 Uart_ReceievePeriodic(u8* pdata);
void UART_SendNoBlock(u8 data);
u8 UART_ReceieveNoBlock();

void UART_Rx_InterruptEnable(void);
void UART_Rx_InterruptDisable(void);

void UART_Tx_InterruptEnable(void);
void UART_Tx_InterruptDisable(void);

void UART_Rx_SetCallBack(void(*LocalFptr)(void));
void UART_Tx_SetCallBack(void(*LocalFptr)(void));

#endif