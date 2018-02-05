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
	  /*只能为0 1，在程序中固死，将总工程里的枚举中，有限改这个。*/
    OLED_CMD = 0,
    OLED_DATA ,
  	/*OLED*/
	  YES,
	  NO,
	  	  /*按键*/
	  mKEY0_PRES = 1,
	  mKEY1_PRES = 2,
    WKUP_PRES = 3,
	
	  /*速度模式的切换*/
	  FREE,//自由模式，根据上面设置的油门来做动作
	  MODE1,//设置为最慢最稳，220
	  MODE2,
	  MODE3,
	
	
  	MODE4,
	  MODE5,
		MODE6,
};

extern uint16_t defaultMax;//LDC有效差值
extern uint16_t coinDet;//检测到硬币的差值

	
extern uint32_t count;
extern uint32_t endDistance;
extern uint8_t showOledFlag;
extern int16_t Time;
extern uint8_t speedMode;//速度模式切换
extern int32_t LSPEED;
extern int32_t RSPEED;
extern double realSpeed;


#endif 
