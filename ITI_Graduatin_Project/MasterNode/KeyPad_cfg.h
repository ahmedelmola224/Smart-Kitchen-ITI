
#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_



#define ROWS 4
#define COLS 4


#ifdef KEYPAD_PROG

static const u8 KeysArray[ROWS][COLS]=
{
	{'7','8','9','/'},
	{'4','5','6','*'},
	{'1','2','3','-'},
	{'C','0','=','+'}
};

static const DIO_Pin_type KeyPadInputPin[COLS]=
{
	PINA4,
	PINA5,
	PINA6,
	PINA7
} ;

static const DIO_Pin_type KeyPadOutputPin[ROWS]=
{
		PINA0,
		PINA1,
		PINA2,
		PINA3
	
};

#endif





#endif 