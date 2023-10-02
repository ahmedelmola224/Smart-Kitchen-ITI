

#ifndef KEYPAD_INTERFACE_H_
#define KEYPAD_INTERFACE_H_
#include "DIO_interface.h"

#define NO_KEY 'N'

void KEYPAD_Init(void);
u8 KEYPAD_GetKey(void);




#endif 