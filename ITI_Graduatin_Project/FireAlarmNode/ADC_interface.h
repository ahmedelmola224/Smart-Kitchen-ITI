


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_


typedef enum {
	VREF_AREF,
	VREF_VCC,
	VREF_256
	}ADC_VoltRef_type;
	
typedef enum {
		ADC_SCALER_2=1,
		ADC_SCALER_4,
		ADC_SCALER_8,
		ADC_SCALER_16,
		ADC_SCALER_32,
		ADC_SCALER_64,
		ADC_SCALER_128
	}ADC_Prescaler_type;


typedef enum 
{
	CH_0=0,
	CH_1,
	CH_2,
	CH_3,
	CH_4,
	CH_5,
	CH_6,
	CH_7
	}ADC_Channel_type;
	
	
#define ADC_VREF ((u32)5000) 
	
void ADC_Init(ADC_VoltRef_type ref,ADC_Prescaler_type scaler);

u16 ADC_Read(ADC_Channel_type ch);

u16 ADC_ReadVolt(ADC_Channel_type ch);

void ADC_StartConversion(ADC_Channel_type ch);
u8 ADC_PeriodicRead(u16*pdata);



#endif /* ADC_INTERFACE_H_ */