#include "data.h"
#include "sys.h"

uint32_t count = 0;//计数距离
uint32_t endDistance = 715;//小车结束时的行进距离
/*提供给OLED调整*/
uint16_t defaultMax  = 5;//LDC有效差值
uint16_t coinDet = 120;//检测到硬币的差值

void SysInit(void)
{
	  SysTickInit();									//滴答定时器初始化
		LED_Init();											//Led灯初始化PA8
	  beepInit();                     //初始化蜂鸣器�
	  EncoderInit();									//编码器初始化
	  OLED_Init();										//OLED界面初始化
	  KEY_Init();										//按键初始化
    MotorPwmOutputInit();						//电机pwm输出初始化PB4  PB5
	  MotorInit();										//电机控制端口初始化,控制电机正,反,停(TB6612的ANI1,AN2)
    while(!EvmInit());              //LDC1314初始化
}

int main(void)
{
		SysInit();
	  LED0 = !LED0;
	  oledStartInfo();//显示初始化信息以及是否初始成功
	
	  while(1)
		{
		    setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
			  changKeyMenu();
			
			  DelayMs(10);
			  setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
			  if(showMainMenu() == YES)
			  {
					  setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
					  break;
				}
				setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
		}
	
	  setSpeedByMode();//通过设置的模式设置起始油门，实时刷新上去
		DelayMs(1000);//延时一秒开始运动
		count = 0;//把计数距离清空
	  SysTickEnable();
		LED0 = !LED0;
		
		while(1)
		{
			  //循迹控制
				TackingControl();
			  //比较距离终点的位置
			  compareDistance();
			  //显示OLED提示信息
			  if(showOledFlag == YES)
				{
					  showOledFlag = NO;
			      showTimeAndDistance();
				}
				//急停按钮
				quickStopKey();
				
		}
}


