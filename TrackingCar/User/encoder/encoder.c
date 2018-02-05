#include "encoder.h"

static void EncoderGpioConfig(void)
{
		GPIO_InitTypeDef GpioInitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_ENCODER_PORT, ENABLE); 
	
		GpioInitStructure.GPIO_Pin = ENCODER_GPIO_PIN;
		GpioInitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(ENCODER_GPIO_PORT, &GpioInitStructure);
}

void EncoderInit(void)
{
		TIM_TimeBaseInitTypeDef	TimTimeBaseInitStructure;
	
		EncoderGpioConfig();
		
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,  ENABLE);	
	
		TIM_DeInit(TIM2);
		TimTimeBaseInitStructure.TIM_Period = 0xFFFF;
		TimTimeBaseInitStructure.TIM_Prescaler = 0;
		TimTimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TimTimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TimTimeBaseInitStructure.TIM_RepetitionCounter = 0;							//ÖØ¸´¼Ä´æÆ÷
		TIM_TimeBaseInit(TIM2, &TimTimeBaseInitStructure);

		TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE);	
	
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,  ENABLE);
		TIM_DeInit(TIM1);
		TimTimeBaseInitStructure.TIM_Period = 0xFFFF;
		TimTimeBaseInitStructure.TIM_Prescaler = 0;
		TimTimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
		TimTimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
		TimTimeBaseInitStructure.TIM_RepetitionCounter = 0;							//ÖØ¸´¼Ä´æÆ÷
		TIM_TimeBaseInit(TIM1, &TimTimeBaseInitStructure);
		
		TIM_ETRClockMode2Config(TIM1, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
		TIM_SetCounter(TIM1, 0);
		TIM_Cmd(TIM1, ENABLE);	
}


