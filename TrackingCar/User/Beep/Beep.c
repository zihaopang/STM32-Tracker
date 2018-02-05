#include "data.h"

void beepInit()
{
	RCC->APB2ENR|=1<<3;    	//使能PORTB时钟	   	  
	GPIOB->CRH&=0XFFFFFFF0; 
	GPIOB->CRH|=0X00000003;	//PB.8 推挽输出    
	BEEP = 0;					//关闭蜂鸣器输出
}

