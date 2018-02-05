#include <stm32f10x.h>
#include "SysTick.h"

int16_t L, R;

uint8_t showOledFlag = NO;//显示标志位

#define upDataTime 30


void SysTick_Handler(void)//1ms一次中断
{
		static int16_t time = 0;
	  static uint32_t i = 0;
	
		time++;
		i ++;
		
	  //3ms一次，控制电机有效，进行动作
	  if(time <= upDataTime)
		{ 
			  time = 0; 
			  Motor.ContorFlag = 1;
    }
		
		
		//一秒一次，显示OLED
		if(i >= 10000)
		{
			  i = 0;
			  showOledFlag = YES;
			  Time ++;//实时时间
    }
}

void SysTickInit(void)
{
		/* SystemFrequency / 1000    1ms中断一次
		 * SystemFrequency / 100000	 10us中断一次
		 * SystemFrequency / 1000000 1us中断一次
		 */
		if (SysTick_Config(SystemCoreClock / 10000))				//72MHz,向下计数,1ms中断
		{ 
				while (1);
		}
			// 关闭滴答定时器  
		SysTickDisable();
}

void SysTickEnable(void)
{
		SysTick->CTRL |=  SysTick_CTRL_ENABLE_Msk;
}

void SysTickDisable(void)
{
		SysTick->CTRL &= ~ SysTick_CTRL_ENABLE_Msk;
}
