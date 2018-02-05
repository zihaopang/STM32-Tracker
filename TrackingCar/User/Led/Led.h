#ifndef __LED_H
#define __LED_H

#include "sys.h"
#include "data.h"

#define LED0 PBout(5)	// DS0
#define LED1 PEout(5)	// DS1	

extern void LED_Init(void);

#endif 
