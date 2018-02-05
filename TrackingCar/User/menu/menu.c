#include "data.h"

extern u8  confirmFlag;//确认标志位
int arrowLocY = OLEDMAXY;//箭头位置
int16_t Time = 0;
//起始提示信息
void oledStartInfo()
{
	  OLED_Clear();	
	  OLED_ShowString(0,0,"Hello World!",16);
	  
	  OLED_ShowString(0,2,"Tracking Car",16);
	
	  OLED_ShowString(0,4,"Please Waiting",16);
	
	  DelayMs(1000);
	
	  OLED_Clear();
	  OLED_ShowString(0,2,"Init  OK!",16);
}


int showMainMenu()
{
	  char tempBuf[20] = {0};

#if 1
		//显示箭头
		OLED_ShowString(0,arrowLocY,">",16);
		
		//显示提示信息    
		sprintf(tempBuf,"LEFT SPEED:%d",LSPEED);
		OLED_ShowString(8,0,tempBuf,16);
	
    //显示提示信息
		sprintf(tempBuf,"RIGHT SPEED:%d",RSPEED);
	  OLED_ShowString(8,2,tempBuf,16);
#endif
    //显示最长行进距离
		sprintf(tempBuf,"Max way:%d",endDistance);
		OLED_ShowString(8,0,tempBuf,16);

    //选择速度模式，如果是任意模式，那么就按照上面设置基础油门，然后运作
    //不然就按照固定的赛道速度   

		switch(speedMode)
    {
			  case FREE:{sprintf(tempBuf,"Speed Mode:AUTO");break;}//默认为自动的
        case MODE1:{sprintf(tempBuf,"Speed Mode:SLOW");break;}//没有增加直线油门
				case MODE2:{sprintf(tempBuf,"Speed Mode:MID");break;}//增加一部分直线油门
				case MODE3:{sprintf(tempBuf,"Speed Mode:FAST");break;}//增加多一点直线油门
				case MODE4:{sprintf(tempBuf,"Speed Mode:MOST");break;}//增加最多的油门
				default:{sprintf(tempBuf,"Speed Mode:ATUO");break;}//默认就是自动的
		}
		setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
		OLED_ShowString(8,2,tempBuf,16);
		//显示检测线圈的差值
		sprintf(tempBuf,"Valid Def:%d",defaultMax);
	  OLED_ShowString(8,4,tempBuf,16);
		
		
	  //显示检测线圈的差值
		sprintf(tempBuf,"Coin Def:%d",coinDet);
		OLED_ShowString(8,6,tempBuf,16);
		
		//确认按钮已经按下
		if(confirmFlag == YES)
		{
			  OLED_ShowString(0,0," ",16);
			  OLED_ShowString(0,2," ",16);
			  OLED_ShowString(0,4," ",16);
			  OLED_ShowString(0,6," ",16);
			  OLED_ShowString(0,8," ",16);
			  return YES;
		}
		return NO;
}


/*显示时间和距离*/
void showTimeAndDistance(void)
{
	  char tempBuf[20] = {0};
		OLED_Clear();
		//显示提示信息
		sprintf(tempBuf,"TIME:%d S",Time);
		OLED_ShowString(8,0,tempBuf,16);
		
				//显示提示信息
		sprintf(tempBuf,"Distance:%d CM",count);
		OLED_ShowString(8,10,tempBuf,16);

    //速度提示
    sprintf(tempBuf,"Speed:%5.2f CM/S",(count*1.0/Time*1.0));
		OLED_ShowString(8,30,tempBuf,16);
}
