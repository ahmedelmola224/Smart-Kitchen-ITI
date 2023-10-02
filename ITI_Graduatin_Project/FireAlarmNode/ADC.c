#include "StdTypes.h"
#include "MemoryMap.h"
#include "Utils.h"
#include "ADC_interface.h"

static u8 ADC_flag=1;
void ADC_Init(ADC_VoltRef_type ref,ADC_Prescaler_type scaler)
{
	//prescaler
	ADCSRA=ADCSRA&0xF8; //11111000
	scaler=scaler&0x07; //00000111
	ADCSRA=ADCSRA|scaler;
	
	/*ref*/
	switch(ref)
	{
		case VREF_AREF:
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_VCC:
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
		break;
		case VREF_256:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
		
	}
	
	/*enable*/
	SET_BIT(ADCSRA,ADEN);
}

u16 ADC_Read(ADC_Channel_type ch)
{
	u16 adc;
	/*select ch*/
	ADMUX=ADMUX&0xE0; //1110 0000
	ADMUX=ADMUX|ch;
	
	/*start conversion*/
	SET_BIT(ADCSRA,ADSC);
	/*wait to end*/
	while(READ_BIT(ADCSRA,ADSC));
	/*read data*/
	adc=ADCL;
	adc+=((ADCH)<<8);
	
	//adc=ADC;
	return adc;
}


void ADC_StartConversion(ADC_Channel_type ch)
{
	if(ADC_flag)
	{
		/*select ch*/
		ADMUX=ADMUX&0xE0; //1110 0000
		ADMUX=ADMUX|ch;
			
		/*start conversion*/
		SET_BIT(ADCSRA,ADSC);
		ADC_flag=0;
	}

}

u8 ADC_PeriodicRead(u16*pdata)
{
	u16 adc;
	if(READ_BIT(ADCSRA,ADSC))
	{
		/*read data*/
		adc=ADCL;
		adc+=((ADCH)<<8);
		*pdata=adc;
		ADC_flag=1;
		return 1;
	}
	return 0;
	
}

u16 ADC_ReadVolt(ADC_Channel_type ch)
{
	u16 adc=ADC_Read(ch);
	u16 volt =((ADC_VREF*adc)/1024);
	return volt;
}

