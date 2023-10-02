

#ifndef SERVO_H_
#define SERVO_H_

#include "StdTypes.h"
#include "Timers.h"


//output on OCR1B
#define TIMER1TOP ICR1      /*ICR1      OCR1A*/
//timer top need to be 19999


void SERVO_Init(void);

void SERVO_Angle(u8 angle);//resolution is 1 degree




#endif 