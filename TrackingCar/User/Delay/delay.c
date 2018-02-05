#include "delay.h"

void DelayUs(u16 time)
{
	u16 i = 0;
	while(time--)
	{
		i = 10;
		while(i--);
	}
}

void DelayMs(u16 time)
{
	u16 i = 0;
	while(time--)
	{
		i = 12000;
		while(i--);
	}
}
