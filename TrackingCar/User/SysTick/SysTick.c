#include <stm32f10x.h>
#include "SysTick.h"

int16_t L, R;

uint8_t showOledFlag = NO;//��ʾ��־λ

#define upDataTime 30


void SysTick_Handler(void)//1msһ���ж�
{
		static int16_t time = 0;
	  static uint32_t i = 0;
	
		time++;
		i ++;
		
	  //3msһ�Σ����Ƶ����Ч�����ж���
	  if(time <= upDataTime)
		{ 
			  time = 0; 
			  Motor.ContorFlag = 1;
    }
		
		
		//һ��һ�Σ���ʾOLED
		if(i >= 10000)
		{
			  i = 0;
			  showOledFlag = YES;
			  Time ++;//ʵʱʱ��
    }
}

void SysTickInit(void)
{
		/* SystemFrequency / 1000    1ms�ж�һ��
		 * SystemFrequency / 100000	 10us�ж�һ��
		 * SystemFrequency / 1000000 1us�ж�һ��
		 */
		if (SysTick_Config(SystemCoreClock / 10000))				//72MHz,���¼���,1ms�ж�
		{ 
				while (1);
		}
			// �رյδ�ʱ��  
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
