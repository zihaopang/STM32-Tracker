#ifndef __KEY_H
#define __KEY_H	 
#include "data.h"


 /*按键*/
#define mKEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)  //PE4
#define mKEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)   //PE5
#define WK_UP  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)   //PA0   KEY_UP

extern void KEY_Init(void);	//IO初始化
extern u8 KEY_Scan(u8);  		//按键扫描函数					    
extern void changKeyMenu(void);
extern void quickStopKey(void);

#endif
