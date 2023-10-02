#ifndef TWI_H_
#define TWI_H_

#include "MemoryMap.h"
#include "StdTypes.h"
#include "Utils.h"


#define TWI_MT_ARB_LOST       0x38
#define TWI_MR_ARB_LOST       0x38
#define TWI_START             0x08
#define TWI_REP_START         0x10
#define TWI_MT_SLV_ACK        0x18
#define TWI_MT_DATA_ACK       0x28
#define TWI_MR_DATA_NOT_ACK   0x58
#define TWI_MT_DATA_NOT_ACK   0x30
#define TWI_MR_SLV_NOT_ACK    0x48
#define TWI_MT_SLV_NOT_ACK    0x20
#define TWI_MR_DATA_ACK       0x50
#define TWI_MR_SLV_ACK        0x40


#define TWI_READ  1
#define TWI_WRITE 0
void TWI_Init(u8 Copy_u8TwiAddress);

void TWI_SlaveInit(u8 Copy_u8TwiAddress);

void TWI_Start(void);

void TWI_Stop(void);

void TWI_WriteAdress(u8 Copy_u8SlaveAddress,u8 Copy_u8ReadWriteBit);

void TWI_WriteData(u8 Copy_u8data);

u8 TWI_ReadData(void);

u8 TWI_GetStatus(void);

#endif /* I2C_H_ */