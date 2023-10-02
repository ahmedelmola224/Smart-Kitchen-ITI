/*
 * EEPROM.h
 *
 * Created: 9/3/2023 4:03:09 PM
 *  Author: ahmed
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "StdTypes.h"

#define A2_pin  0
#define EEPROM_FIXED_SEQ 0x50
void EEPROM_WriteString(u16 address,u8*str);
void EEPROM_ReadString(u16 address,u8*str);

#endif /* EEPROM_H_ */