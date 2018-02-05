#ifndef __TACK_H
#define __TACK_H

#include "data.h"

#define RCC_TACK_PORT	RCC_APB2Periph_GPIOA
#define TACK_GPIO_PORT	GPIOA
#define TACK_GPIO_PIN		GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7

#define OUT 5 //转出去了再转大弯

extern void TackInit(void);
extern int8_t GetPosition(void);

#endif 
