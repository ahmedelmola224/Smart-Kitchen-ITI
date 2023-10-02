#include "STOVE_interface.h"



int main(void)
{
	STOVE_Init();
    while (1) 
    {
		STOVE_Runnable();
    }
}

