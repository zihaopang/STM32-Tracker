#include "data.h"
#include "sys.h"

uint32_t count = 0;//¼ÆÊı¾àÀë
uint32_t endDistance = 715;//Ğ¡³µ½áÊøÊ±µÄĞĞ½ø¾àÀë
/*Ìá¹©¸øOLEDµ÷Õû*/
uint16_t defaultMax  = 5;//LDCÓĞĞ§²îÖµ
uint16_t coinDet = 120;//¼ì²âµ½Ó²±ÒµÄ²îÖµ

void SysInit(void)
{
	  SysTickInit();									//µÎ´ğ¶¨Ê±Æ÷³õÊ¼»¯
		LED_Init();											//LedµÆ³õÊ¼»¯PA8
	  beepInit();                     //³õÊ¼»¯·äÃùÆ÷¯
	  EncoderInit();									//±àÂëÆ÷³õÊ¼»¯
	  OLED_Init();										//OLED½çÃæ³õÊ¼»¯
	  KEY_Init();										//°´¼ü³õÊ¼»¯
    MotorPwmOutputInit();						//µç»úpwmÊä³ö³õÊ¼»¯PB4  PB5
	  MotorInit();										//µç»ú¿ØÖÆ¶Ë¿Ú³õÊ¼»¯,¿ØÖÆµç»úÕı,·´,Í£(TB6612µÄANI1,AN2)
    while(!EvmInit());              //LDC1314³õÊ¼»¯
}

int main(void)
{
		SysInit();
	  LED0 = !LED0;
	  oledStartInfo();//ÏÔÊ¾³õÊ¼»¯ĞÅÏ¢ÒÔ¼°ÊÇ·ñ³õÊ¼³É¹¦
	
	  while(1)
		{
		    setSpeedByMode();//Í¨¹ıÉèÖÃµÄÄ£Ê½ÉèÖÃÆğÊ¼ÓÍÃÅ£¬ÊµÊ±Ë¢ĞÂÉÏÈ¥
			  changKeyMenu();
			
			  DelayMs(10);
			  setSpeedByMode();//Í¨¹ıÉèÖÃµÄÄ£Ê½ÉèÖÃÆğÊ¼ÓÍÃÅ£¬ÊµÊ±Ë¢ĞÂÉÏÈ¥
			  if(showMainMenu() == YES)
			  {
					  setSpeedByMode();//Í¨¹ıÉèÖÃµÄÄ£Ê½ÉèÖÃÆğÊ¼ÓÍÃÅ£¬ÊµÊ±Ë¢ĞÂÉÏÈ¥
					  break;
				}
				setSpeedByMode();//Í¨¹ıÉèÖÃµÄÄ£Ê½ÉèÖÃÆğÊ¼ÓÍÃÅ£¬ÊµÊ±Ë¢ĞÂÉÏÈ¥
		}
	
	  setSpeedByMode();//Í¨¹ıÉèÖÃµÄÄ£Ê½ÉèÖÃÆğÊ¼ÓÍÃÅ£¬ÊµÊ±Ë¢ĞÂÉÏÈ¥
		DelayMs(1000);//ÑÓÊ±Ò»Ãë¿ªÊ¼ÔË¶¯
		count = 0;//°Ñ¼ÆÊı¾àÀëÇå¿Õ
	  SysTickEnable();
		LED0 = !LED0;
		
		while(1)
		{
			  //Ñ­¼£¿ØÖÆ
				TackingControl();
			  //±È½Ï¾àÀëÖÕµãµÄÎ»ÖÃ
			  compareDistance();
			  //ÏÔÊ¾OLEDÌáÊ¾ĞÅÏ¢
			  if(showOledFlag == YES)
				{
					  showOledFlag = NO;
			      showTimeAndDistance();
				}
				//¼±Í£°´Å¥
				quickStopKey();
				
		}
}


