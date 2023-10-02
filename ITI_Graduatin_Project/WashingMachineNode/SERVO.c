#include "SERVO.h"

void SERVO_Init(void)
{
	Timer1_OCRB1Mode(OCRA_NON_INVERTING);
	TIMER1TOP=19999;
	
}

void SERVO_Angle(u8 angle)
{
	OCR1B=999+(angle*(u32)1000)/180;
}