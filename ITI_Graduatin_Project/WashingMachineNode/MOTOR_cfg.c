#include "StdTypes.h"
#include "DIO_interface.h"
#include "MOTOR_cfg.h"
#include "MOTOR_private.h"

const DIO_Pin_type MotorPinsArray[NUMBER_OF_MOTORS][NUMBER_OF_PINS_PER_MOTOR]=
{
					/*IN1  IN2*/
	
	/*motor1*/		{PIND5,PIND6}
};
