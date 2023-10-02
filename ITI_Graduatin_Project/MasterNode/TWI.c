#include "TWI.h"

void TWI_Init(u8 Copy_u8TwiAddress)
{
	//TWI Initialization
	//Bit Rate : 50.000 kHz (m7taga tet3adel
	TWBR = 72 ;
	//I2C Bus Slave Address : Copy_u8TwiAdress
	//General Call Recognition : Off
	TWAR = (Copy_u8TwiAddress<<1);
	//Generate Acknowledge Pulse : On
	//I2C Interrupt : Off
	TWCR = 0x44 ;
	TWSR = 0x00 ;
	TWSR &=(~((1<<TWPS1) | (1<<TWPS0)));
}

void TWI_Start(void)
{
	
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	// Wait for TWINT Flag Set in TWCR Register
	while(!(TWCR & (1<<TWINT)));
}

void TWI_Stop(void)
{
	
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);
}

void TWI_WriteAdress(u8 Copy_u8SlaveAddress,u8 Copy_u8ReadWriteBit)
{
	u8 LOC_u8Frame=Copy_u8ReadWriteBit | (Copy_u8SlaveAddress<<1);
	TWDR=LOC_u8Frame;
	/*Clear the flag*/
	TWCR = (1<<TWINT) | (1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
}

void TWI_WriteData(u8 Copy_u8data)
{
	//put data in TWI Register
	TWDR = Copy_u8data ;
	/*Clear the flag*/
	TWCR = (1<<TWINT) | (1<<TWEN);
	// Wait for TWINT Flag Set in TWCR Register
	while(!(TWCR & (1<<TWINT)));
}

/*Read the data recived after sending ack */
u8 TWI_ReadData(void)
{
	/*Clear the flag*/
	SET_BIT(TWCR,TWINT);
	// Wait for TWINT Flag Set in TWCR Register
	while(!(TWCR & (1<<TWINT)));
	//Read Data
	return TWDR ;
}


u8 TWI_GetStatus(void)
{
	u8 status ;
	status = TWSR & 0xF8 ;
	return status ;
}