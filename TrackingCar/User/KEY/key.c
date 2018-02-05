#include "data.h"

int testMenuLast; 	
extern int arrowLocY;
u8  confirmFlag = NO;//确认按钮

//按键初始化函数
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟
	RCC->APB2ENR|=1<<6;     //使能PORTE时钟
	GPIOA->CRL&=0XFFFFFFF0;	//PA0设置成输入，默认下拉	  
	GPIOA->CRL|=0X00000008; 
	  
	GPIOE->CRL&=0XFFF00FFF;	//PE3/4设置成输入	  
	GPIOE->CRL|=0X00088000; 				   
	GPIOE->ODR|=3<<3;	   	//PE3/4 上拉
} 

//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//返回值:
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下 
//3，KEY_UP按下 即WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(mKEY0==0 || mKEY1==0 || WK_UP==1))
	{
		DelayMs(10);//去抖动 
		key_up=0;
		if(mKEY0==0)return 1;
		else if(mKEY1==0)return 2; 
		else if(WK_UP==1)return 3;
	}else if(mKEY0==1 && mKEY1==1 && WK_UP==0)key_up=1; 	    
 	return 0;// 无按键按下
}


//急停按钮检测，在运行时，无论按什么都停下
void quickStopKey(void)
{
	  char buf[50] = {0};
	
	  //一旦有按键按下，就立马停机
	  if((mKEY0==0)|| (mKEY1==0) || (WK_UP==0))
		{
			  MOTOR_STOP;//马达停止
				TIM_Cmd(TIM3, DISABLE);
				showTimeAndDistance();
				SysTickDisable();
			
			  OLED_Clear();
			  memset(buf, 0, sizeof(buf));
				sprintf(buf, "distance:%d", count);
			  OLED_ShowString(0,0,buf,16);
			
				sprintf(buf, "Time:%d",Time);
			  OLED_ShowString(0,2,buf,16);
			
			  BEEP = BEEP;
			  
				while(1);
		}
}

/*根据按键，修改阀值*/
void changKeyMenu(void)
{
	  u8 key;	
	  key = KEY_Scan(0);//不支持连按
		if(key)
		{
				switch(key)
				{					
						case WKUP_PRES:
						{ 
							  confirmFlag = YES;
                arrowLocY += OLEDMODFIY;
							  if(arrowLocY > OLEDMAXY)
								{
									  arrowLocY = OLEDMINY;
								}
								OLED_Clear();
							  showMainMenu();//刷新显示					
								break;
						}
						case mKEY0_PRES:
						{
							 switch(arrowLocY)
								{
										case 0:{ //左轮速度
											if(speedMode == FREE)//只有自动模式才能设置速度
											{
												LSPEED -= 10;
											  if(LSPEED <= 80)
												{
													  LSPEED = 900;
												}
											}
											break;
										}
										case 10:{//右轮速度
											if(speedMode == FREE)//只有自动模式才能设置速度
											{
                        RSPEED -= 10;
											  if(RSPEED <= 80)
												{
													  RSPEED = 900;
												}
											}
											break;
										}
										case 20:{//行驶距离
												endDistance -= 5;
											  if(endDistance <= 6) //不允许为负
												{
													  endDistance = 700;
												}
												break;
										}
										case 30:{//固定基础油门增加速度部分
											  if(speedMode == FREE)	
												{
													  speedMode = MODE4;
												}
											  else if(speedMode == MODE4)
												{
													  speedMode = MODE3;
												}
												else if(speedMode == MODE3)
												{
													  speedMode = MODE2;
												}
												else if(speedMode == MODE2)
												{
													  speedMode = MODE1;
												}
												else if(speedMode == MODE1)
												{
													  speedMode = FREE;
												}
													
												
												//立即刷新，将数据显示上去
												OLED_Clear();
											  showMainMenu();//刷新整屏显示
												break;
										}
										case 40:{//有效电感的显示											  																				
												defaultMax --;
											  if(defaultMax <= 1)
												{
													  defaultMax = 20;
												}											
												break;
										}
										case 50:{//硬币检测																						
												coinDet -= 15;
											  if(coinDet <= 30)
												{
													  coinDet = 500;
												}
											
												break;
										}
								}
							 
								OLED_Clear();
								showMainMenu();//刷新整屏显示													
								break;
					}
            case mKEY1_PRES:
						{
							switch(arrowLocY)
								{
										case 0:{
											if(speedMode == FREE)//只有自动模式才能设置速度
											{
												LSPEED += 10;
											  if(LSPEED > 900)
												{
													  LSPEED = 100;
												}
											}
											break;
									
										}
										case 10:{
											if(speedMode == FREE)//只有自动模式才能设置速度
											{
                        RSPEED += 10;
											  if(RSPEED > 900)
												{
													  RSPEED = 100;
												}
											}
											break;
										}
										case 20:{
												endDistance += 5;
											  if(endDistance >= 4000)//多于4m则回到500
												{
													  endDistance = 400;
												}
												break;
										}
										case 30:{//基础油门上增加
												if(speedMode == FREE)
												{
													  speedMode = MODE1;
												}
												else if(speedMode == MODE1)
												{
													  speedMode = MODE2;
												}
												else if(speedMode == MODE2)
												{
													  speedMode = MODE3;
												}
												else if(speedMode == MODE3)
												{
													  speedMode = MODE4;
												}
												else if(speedMode == MODE4)
												{
													  speedMode = FREE;
												}
											
											
												//立即刷新，将数据显示上去
											  OLED_Clear();
											  showMainMenu();//刷新整屏显示												
												break;
										}
										case 40:{//有效检测铁丝
												defaultMax ++;
											  if(defaultMax >= 100)
												{
													  defaultMax = 1;
												}	
												break;
										}
										case 50:{
												coinDet += 15;
											  if(coinDet >= 1000)
												{
													  coinDet = 450;
												}
												break;
										}										
								}
							 
								OLED_Clear();
								showMainMenu();//刷新整屏显示																	
						    break;
						}						
				}
		}
}
