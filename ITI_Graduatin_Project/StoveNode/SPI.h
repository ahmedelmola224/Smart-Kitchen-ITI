/*
 * SPI.h
 *
 * Created: 3/5/2023 10:04:05 PM
 *  Author: ahmed
 */ 


#ifndef SPI_H_
#define SPI_H_

#define MASTER 1
#define SLAVE  0 

#define SPIMODE SLAVE

void SPI_Init(void);
u8 SPI_SendReceieve(u8 data);

void SPI_SendNoBlock(u8 data);
u8 SPI_ReceieveNoBlock(void);
u8 SPI_ReceievePeriodic(u8 *pdata);
void SPI_InterruptEnable(void);
void SPI_InterruptDisable(void);
void SPI_SetCallBack(void(*LocalFptr)(void));

#endif /* SPI_H_ */