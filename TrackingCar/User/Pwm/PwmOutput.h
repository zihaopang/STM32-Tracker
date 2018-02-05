#ifndef __PWM_OUTPUT_H
#define __PWM_OUTPUT_H

#include "data.h"

#define RCC_PWM_PORT	RCC_APB2Periph_GPIOB
#define PWM_GPIO_PORT	GPIOB
#define PWM_MOTOR_OUT GPIO_Pin_4 | GPIO_Pin_5		  //电机pwm输出端口

extern void ServoPwmOutputInit(void);
extern void MotorPwmOutputInit(void);

#endif 
