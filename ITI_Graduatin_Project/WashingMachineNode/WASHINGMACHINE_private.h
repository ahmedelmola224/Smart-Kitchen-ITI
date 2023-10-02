

#ifndef WASHINGMACHINE_PRIVATE_H_
#define WASHINGMACHINE_PRIVATE_H_


static void WM_Interrupt();
static void WASHINGMACHINE_voidSetMode(u8 Mode);
static void WASHINGMCHINE_voidStopMode();
#define WM_NOT_WORKING	  0
#define WM_WORKING        1

#define BLACK_CLOTHES_MODE  '1'
#define WHITE_CLOTHES_MODE  '2'
#define HOT_WATER_MODE      '3'
#define COLD_WATER_MODE     '4'



#endif 