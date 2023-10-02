#include "StdTypes.h"
#include "ADC_interface.h"
#include "Sensors.h"



u16 PRESSURE_Read()
{
	u16 adc;
	u16 pressure;
	adc=ADC_Read(MPX4115_CH);
	pressure=(((u32)(adc-55)*1000)/921)+150;
	return pressure;
}

/*1->.5v*/
u16 TEMP_Read(void)
{
	u16 temp ,adc;
	adc=ADC_Read(LM35_CH);
	temp=(adc*(u32)300)/307;
	return temp;
}