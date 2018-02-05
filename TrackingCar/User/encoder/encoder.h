#ifndef __ENCODER_H
#define __ENCODER_H

#include "data.h"

#define RCC_ENCODER_PORT	RCC_APB2Periph_GPIOD
#define ENCODER_GPIO_PORT	GPIOD
#define ENCODER_GPIO_PIN	GPIO_Pin_11 | GPIO_Pin_12

extern void EncoderInit(void);

#endif
