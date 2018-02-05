#include "tack.h"

void TackGpioConfig(void)
{
		GPIO_InitTypeDef GpioInitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_TACK_PORT, ENABLE); 
	
		GpioInitStructure.GPIO_Pin = TACK_GPIO_PIN;
		GpioInitStructure.GPIO_Mode = GPIO_Mode_IPU;
		GpioInitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
		GPIO_Init(TACK_GPIO_PORT, &GpioInitStructure);
}

void TackInit(void)
{
		TackGpioConfig();
}



int8_t GetPosition(void)
{
		static int8_t position = 0;
		__IO uint16_t data;
	
		data = (GPIO_ReadInputData(TACK_GPIO_PORT) >> 4) & 0x000F;
	
		switch(data)
		{	
			  case 0x0000:						
			  {
						if(3 == position) { position = 4; }
						else if(-3 == position) { position = -4; }
						else if(1 == position){position = 0;}
						else if(-1 == position) {position = 0;}
						break;	
				}//×î´óÍä
				case 0x0001: position = -3; break;
				case 0x0002: position = -1; break;
				case 0x0003: position = -2; break;
				case 0x0004: position = 1; break;
				case 0x0008: position = 3; break;
				case 0x000C: position = 2; break;
				case 0x000F: position = 0; break;
				default : break;
		}
		
		return position;
}


