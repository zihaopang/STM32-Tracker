#include "data.h"

uint8_t speedMode = FREE;//定义变量，用来计数模式

//通过模式来设置速度，在确认按钮按下的那一刻做一次
void setSpeedByMode(void)
{
	  if(speedMode != FREE)//如果不是自动模式
		{
			  //设置两个电机的基础速度，在这个基础上准备增加速度
			  LSPEED = 220;
			  RSPEED = 220;
		}
}
