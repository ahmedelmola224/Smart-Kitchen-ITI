#include "StdTypes.h"
#include "DIO_interface.h"

const DIO_PinStatus_type PinStatusArray[TOTAL_PINS]=
{
	INFREE,/*Port A Pin 0*/
	INFREE,/*Port A Pin 1*/
	OUTPUT,/*Port A Pin 2*/
	OUTPUT,/*Port A Pin 3*/
	INPULL,/*Port A Pin 4*/
	INPULL,/*Port A Pin 5*/
	INPULL,/*Port A Pin 6*/
	INPULL,/*Port A Pin 7*/
	OUTPUT,/*Port B Pin 0*/
	OUTPUT,/*Port B Pin 1*/
	OUTPUT,/*Port B Pin 2*/
	OUTPUT,/*Port B Pin 3  OC0*/
	INFREE,/*Port B Pin 4 SS*/
	OUTPUT,/*Port B Pin 5   MOSI*/
	INFREE,/*Port B Pin 6    MISO*/
	OUTPUT,/*Port B Pin 7     SCK*/
	OUTPUT,/*Port C Pin 0*/
	OUTPUT,/*Port C Pin 1*/
	OUTPUT,/*Port C Pin 2*/
	OUTPUT,/*Port C Pin 3*/
	OUTPUT,/*Port C Pin 4*/
	OUTPUT,/*Port C Pin 5*/
	OUTPUT,/*Port C Pin 6*/
	OUTPUT,/*Port C Pin 7*/
	INFREE,/*Port D Pin 0*/
	OUTPUT,/*Port D Pin 1*/
	OUTPUT,/*Port D Pin 2  int0*/
	OUTPUT,/*Port D Pin 3  int1*/
	OUTPUT,/*Port D Pin 4  OCR1B*/
	OUTPUT,/*Port D Pin 5  OCR1A*/
	OUTPUT,/*Port D Pin 6   icp1*/
	OUTPUT /*Port D Pin 7*/
};
