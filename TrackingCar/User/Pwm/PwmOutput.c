#include "PwmOutput.h"

void MotorPwmGpioConfig(void)
{
		GPIO_InitTypeDef GpioInitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_PWM_PORT, ENABLE); 
		GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
	
		GpioInitStructure.GPIO_Pin = PWM_MOTOR_OUT;
		GpioInitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
		GpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(PWM_GPIO_PORT, &GpioInitStructure);
}

void MotorPwmOutputInit(void)
{
		TIM_TimeBaseInitTypeDef	TimTimeBaseInitStructure;
		TIM_OCInitTypeDef TimOcInitStructure;
	
		MotorPwmGpioConfig();
	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
		TimTimeBaseInitStructure.TIM_Period = 999;
		TimTimeBaseInitStructure.TIM_Prescaler = 72 - 1;
		TimTimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TimTimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TimTimeBaseInitStructure.TIM_RepetitionCounter = 0;							//重复寄存器
	
		TIM_TimeBaseInit(TIM3, &TimTimeBaseInitStructure);
	
		TimOcInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
		TimOcInitStructure.TIM_OutputState = TIM_OutputState_Enable;
		TimOcInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
		TimOcInitStructure.TIM_Pulse = 100;
		TIM_OC1Init(TIM3, &TimOcInitStructure);
		TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TimOcInitStructure.TIM_Pulse = 100;
		TIM_OC2Init(TIM3, &TimOcInitStructure);
		TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
		
		TIM_ARRPreloadConfig(TIM3, ENABLE);															//允许计数器的ARR自动重载缓冲
		TIM_Cmd(TIM3, ENABLE);
}

//TIM_SetComparen		该函数改变pwm输出占空比
//TIM_SetAutoreload 该函数改变pwm输出周期
