#include "data.h"

int testMenuLast; 	
extern int arrowLocY;
u8  confirmFlag = NO;//ȷ�ϰ�ť

//������ʼ������
void KEY_Init(void)
{
	RCC->APB2ENR|=1<<2;     //ʹ��PORTAʱ��
	RCC->APB2ENR|=1<<6;     //ʹ��PORTEʱ��
	GPIOA->CRL&=0XFFFFFFF0;	//PA0���ó����룬Ĭ������	  
	GPIOA->CRL|=0X00000008; 
	  
	GPIOE->CRL&=0XFFF00FFF;	//PE3/4���ó�����	  
	GPIOE->CRL|=0X00088000; 				   
	GPIOE->ODR|=3<<3;	   	//PE3/4 ����
} 

//����������
//���ذ���ֵ
//mode:0,��֧��������;1,֧��������;
//����ֵ:
//0��û���κΰ�������
//1��KEY0����
//2��KEY1���� 
//3��KEY_UP���� ��WK_UP
//ע��˺�������Ӧ���ȼ�,KEY0>KEY1>KEY_UP!!
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//�������ɿ���־
	if(mode)key_up=1;  //֧������		  
	if(key_up&&(mKEY0==0 || mKEY1==0 || WK_UP==1))
	{
		DelayMs(10);//ȥ���� 
		key_up=0;
		if(mKEY0==0)return 1;
		else if(mKEY1==0)return 2; 
		else if(WK_UP==1)return 3;
	}else if(mKEY0==1 && mKEY1==1 && WK_UP==0)key_up=1; 	    
 	return 0;// �ް�������
}


//��ͣ��ť��⣬������ʱ�����۰�ʲô��ͣ��
void quickStopKey(void)
{
	  char buf[50] = {0};
	
	  //һ���а������£�������ͣ��
	  if((mKEY0==0)|| (mKEY1==0) || (WK_UP==0))
		{
			  MOTOR_STOP;//���ֹͣ
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

/*���ݰ������޸ķ�ֵ*/
void changKeyMenu(void)
{
	  u8 key;	
	  key = KEY_Scan(0);//��֧������
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
							  showMainMenu();//ˢ����ʾ					
								break;
						}
						case mKEY0_PRES:
						{
							 switch(arrowLocY)
								{
										case 0:{ //�����ٶ�
											if(speedMode == FREE)//ֻ���Զ�ģʽ���������ٶ�
											{
												LSPEED -= 10;
											  if(LSPEED <= 80)
												{
													  LSPEED = 900;
												}
											}
											break;
										}
										case 10:{//�����ٶ�
											if(speedMode == FREE)//ֻ���Զ�ģʽ���������ٶ�
											{
                        RSPEED -= 10;
											  if(RSPEED <= 80)
												{
													  RSPEED = 900;
												}
											}
											break;
										}
										case 20:{//��ʻ����
												endDistance -= 5;
											  if(endDistance <= 6) //������Ϊ��
												{
													  endDistance = 700;
												}
												break;
										}
										case 30:{//�̶��������������ٶȲ���
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
													
												
												//����ˢ�£���������ʾ��ȥ
												OLED_Clear();
											  showMainMenu();//ˢ��������ʾ
												break;
										}
										case 40:{//��Ч��е���ʾ											  																				
												defaultMax --;
											  if(defaultMax <= 1)
												{
													  defaultMax = 20;
												}											
												break;
										}
										case 50:{//Ӳ�Ҽ��																						
												coinDet -= 15;
											  if(coinDet <= 30)
												{
													  coinDet = 500;
												}
											
												break;
										}
								}
							 
								OLED_Clear();
								showMainMenu();//ˢ��������ʾ													
								break;
					}
            case mKEY1_PRES:
						{
							switch(arrowLocY)
								{
										case 0:{
											if(speedMode == FREE)//ֻ���Զ�ģʽ���������ٶ�
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
											if(speedMode == FREE)//ֻ���Զ�ģʽ���������ٶ�
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
											  if(endDistance >= 4000)//����4m��ص�500
												{
													  endDistance = 400;
												}
												break;
										}
										case 30:{//��������������
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
											
											
												//����ˢ�£���������ʾ��ȥ
											  OLED_Clear();
											  showMainMenu();//ˢ��������ʾ												
												break;
										}
										case 40:{//��Ч�����˿
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
								showMainMenu();//ˢ��������ʾ																	
						    break;
						}						
				}
		}
}
