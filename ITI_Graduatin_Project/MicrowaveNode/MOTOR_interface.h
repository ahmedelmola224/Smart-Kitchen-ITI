
#ifndef MOTOR_INTERFACE_H_
#define MOTOR_INTERFACE_H_

typedef enum
{
	M1=0,
	M2,
	M3,
	M4,
	TOTAL_MOTORS
	}MOTOR_type;

extern void MOTOR_Init();
extern void MOTOR_Stop(MOTOR_type motor);
extern void MOTOR_Cw(MOTOR_type motor);
extern void MOTOR_Ccw(MOTOR_type motor);




#endif 