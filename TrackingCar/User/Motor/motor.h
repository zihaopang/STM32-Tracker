#ifndef __MOTOR_H
#define __MOTOR_H

#include "data.h"
#define RCC_MOTOR_PORT	RCC_APB2Periph_GPIOC
#define MOTOR_GPIO_PORT	GPIOC

#define MOTOR_AIN1_PIN	GPIO_Pin_8
#define MOTOR_AIN2_PIN	GPIO_Pin_9
#define MOTOR_BIN1_PIN  GPIO_Pin_10
#define MOTOR_BIN2_PIN  GPIO_Pin_11

#define SERVO_MID 6

extern int32_t LSPEED;
extern int32_t RSPEED;


#define FOREWARD	1					//����
#define STOP			0					//ֹͣ
#define REVERSE 	-1				//����

#define MOTOR_REVERSE {GPIO_SetBits(MOTOR_GPIO_PORT, MOTOR_AIN1_PIN);\
												GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_AIN2_PIN);\
											  GPIO_SetBits(MOTOR_GPIO_PORT, MOTOR_BIN1_PIN);\
	                       GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_BIN2_PIN);}
#define MOTOR_FOREWARD {GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_AIN1_PIN);\
												GPIO_SetBits(MOTOR_GPIO_PORT, MOTOR_AIN2_PIN);\
                        GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_BIN1_PIN);\
	                       GPIO_SetBits(MOTOR_GPIO_PORT, MOTOR_BIN2_PIN);}
#define MOTOR_STOP	{GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_AIN1_PIN);\
										 GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_AIN2_PIN);\
										 GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_BIN1_PIN);\
										 GPIO_ResetBits(MOTOR_GPIO_PORT, MOTOR_BIN2_PIN);\
}

typedef struct{
		uint8_t ContorFlag;						//���Ʊ�־
		int8_t 	Direction;						//�������
		int8_t  Distance;							//ƫ�����ľ���
		int8_t  Angle;									//����Ƕ�
		int16_t LSpeed;								//���ת��,��PWMռ�ձ�
	  int16_t RSpeed;               //�ұߵ��PWM
}MotorControl;

extern MotorControl Motor;

extern void MotorGpioConfig(void);
extern void MotorInit(void);
extern void SetSpeed(int16_t Lspeed,int16_t Rspeed);

#endif
