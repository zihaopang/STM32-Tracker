#include "motor.h"

int32_t LSPEED = 300;
int32_t RSPEED = 300;

void MotorGpioConfig(void)
{
		GPIO_InitTypeDef GpioInitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_MOTOR_PORT, ENABLE); 
	
		GpioInitStructure.GPIO_Pin = MOTOR_AIN1_PIN | MOTOR_AIN2_PIN | MOTOR_BIN1_PIN | MOTOR_BIN2_PIN;
		GpioInitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
		GpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(MOTOR_GPIO_PORT, &GpioInitStructure);
}

MotorControl Motor;

void MotorInit(void)
{
		MotorGpioConfig();
	
		Motor.ContorFlag = 0;
		Motor.Direction = FOREWARD;
		Motor.Distance = 0;
		Motor.LSpeed = 0;
	  Motor.RSpeed = 0;
}




void SetSpeed(int16_t Lspeed,int16_t Rspeed)
{
		TIM_SetCompare1(TIM3, LSPEED + Lspeed);
	  TIM_SetCompare2(TIM3, RSPEED + Rspeed);
}
