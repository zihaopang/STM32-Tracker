#ifndef __DATA_H
#define __DATA_H

#include "stm32f10x.h"
#include "stm32f10x_tim.h"
#include "stdio.h"
#include "string.h"
#include "led.h"
#include "SysTick.h"
#include "delay.h"
#include "PwmOutput.h"
#include "motor.h"
#include "tack.h"
#include "iic.h"
#include "control.h"
#include "pid.h"
#include "encoder.h"
#include "oled.h"
#include "menu.h"
#include "key.h"
#include "ldc1314.h"
#include "Beep.h"
#include "speedMode.h"

#define OLEDMAXY  50
#define OLEDMINY  0
#define OLEDMODFIY 10
enum All
{
	  /*ֻ��Ϊ0 1���ڳ����й��������ܹ������ö���У����޸������*/
    OLED_CMD = 0,
    OLED_DATA ,
  	/*OLED*/
	  YES,
	  NO,
	  	  /*����*/
	  mKEY0_PRES = 1,
	  mKEY1_PRES = 2,
    WKUP_PRES = 3,
	
	  /*�ٶ�ģʽ���л�*/
	  FREE,//����ģʽ�������������õ�������������
	  MODE1,//����Ϊ�������ȣ�220
	  MODE2,
	  MODE3,
	
	
  	MODE4,
	  MODE5,
		MODE6,
};

extern uint16_t defaultMax;//LDC��Ч��ֵ
extern uint16_t coinDet;//��⵽Ӳ�ҵĲ�ֵ

	
extern uint32_t count;
extern uint32_t endDistance;
extern uint8_t showOledFlag;
extern int16_t Time;
extern uint8_t speedMode;//�ٶ�ģʽ�л�
extern int32_t LSPEED;
extern int32_t RSPEED;
extern double realSpeed;


#endif 
