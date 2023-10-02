/*
 * MASTER_private.h
 *
 * Created: 9/5/2023 1:31:50 PM
 *  Author: ahmed
 */ 


#ifndef MASTER_PRIVATE_H_
#define MASTER_PRIVATE_H_


static void MASTER_voidSendSystemState(void);
static void MASTER_voidSendSystemState(void);
static void WM_voidGetState(void);
static void MASTER_voidSendWashingmachineStop();
static void MASTER_voidSendWashingmachineOrderState(void);
static void MASTER_voidSendMicrowaveOrderState(void);
static void MASTER_voidSendStoveOrderState(void);
static void MASTER_voidShowMenuState(void);
static void MASTER_voidChangeMenuState(void);
static u8 MASTER_CheckPassword(u8*str1,u8*str2);
static void MATSER_voidReceievePassword(u8*str);
static void MASTER_CopyPassword(u8*str1,u8*str2);
static void MASTER_voidGetPassState(void);


/*Master states*/
#define MASTER_CHECK_PASS			0	
#define MASTER_CHANGE_MENU			1
#define MASTER_GET_MENU				2
#define MASTER_ORDER_STOVE			3
#define MASTER_ORDER_MICROWAVE		4
#define MASTER_ORDER_WASHINGMACHINE 5
#define MASTER_ORDER_SYSTEMSTATE    6

/*MASTER_CHECK_PASS states*/
#define MASTER_PASSWORD_LOCATION  0
#define MASTER_WRONG_PASS		  0
#define MASTER_CORRECT_PASS       1

/*MASTER_CHANGE_MENU states*/
#define MASTER_CHANGE_PASS        '1'
#define MASTER_SHOW_MENU          '2'

/*MASTER_GET_MENU states*/
#define MASTER_STOVE               '1'
#define MASTER_MICROWAVE           '2'
#define MASTER_WASHINGMACHINE      '3'
#define MASTER_SYSTEMSTATE		   '4'



/*MASTER_ORDER_STOVE states*/
#define FLAME1                     '1'
#define FLAME2                     '2'
#define FLAME3                     '3'
#define FLAME4                     '4'
#define FLAME5                     '5'
#define FLMAE_ON                   '1'
#define FLAME_OFF                  '2'  

#define MICROWAVE_SET_TIME          '1'
#define MICROWAVE_STOP              '2'


#define WHITE                        '2'
#define BLACK                        '1'
#define HOT                          '3'
#define COLD						 '4'
#define WM_WORKING                   1
#define WM_NOT_WORKING               0
#define MW_STOP                      '1'
#define MW_GETBACK                   '2'





#endif /* MASTER_PRIVATE_H_ */