#include "data.h"

void beepInit()
{
	RCC->APB2ENR|=1<<3;    	//ʹ��PORTBʱ��	   	  
	GPIOB->CRH&=0XFFFFFFF0; 
	GPIOB->CRH|=0X00000003;	//PB.8 �������    
	BEEP = 0;					//�رշ��������
}

