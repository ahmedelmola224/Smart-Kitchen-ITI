#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"



void MOTOR_Init()
{
	/*do nothing */
}

void MOTOR_Stop(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN0],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
	
}

void MOTOR_Cw(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN0],HIGH);
	DIO_WritePin(MotorPinsArray[motor][IN1],LOW);
}

void MOTOR_Ccw(MOTOR_type motor)
{
	DIO_WritePin(MotorPinsArray[motor][IN0],LOW);
	DIO_WritePin(MotorPinsArray[motor][IN1],HIGH);
}

