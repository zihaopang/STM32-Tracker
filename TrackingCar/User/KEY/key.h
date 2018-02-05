#ifndef __KEY_H
#define __KEY_H	 
#include "data.h"


 /*����*/
#define mKEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)  //PE4
#define mKEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)   //PE5
#define WK_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //PA0   KEY_UP

extern void KEY_Init(void);	//IO��ʼ��
extern u8 KEY_Scan(u8);  		//����ɨ�躯��					    
extern void changKeyMenu(void);
extern void quickStopKey(void);

#endif
