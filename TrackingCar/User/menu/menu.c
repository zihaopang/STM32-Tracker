#include "data.h"

extern u8  confirmFlag;//ȷ�ϱ�־λ
int arrowLocY = OLEDMAXY;//��ͷλ��
int16_t Time = 0;
//��ʼ��ʾ��Ϣ
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
		//��ʾ��ͷ
		OLED_ShowString(0,arrowLocY,">",16);
		
		//��ʾ��ʾ��Ϣ    
		sprintf(tempBuf,"LEFT SPEED:%d",LSPEED);
		OLED_ShowString(8,0,tempBuf,16);
	
    //��ʾ��ʾ��Ϣ
		sprintf(tempBuf,"RIGHT SPEED:%d",RSPEED);
	  OLED_ShowString(8,2,tempBuf,16);
#endif
    //��ʾ��н�����
		sprintf(tempBuf,"Max way:%d",endDistance);
		OLED_ShowString(8,0,tempBuf,16);

    //ѡ���ٶ�ģʽ�����������ģʽ����ô�Ͱ����������û������ţ�Ȼ������
    //��Ȼ�Ͱ��չ̶��������ٶ�   

		switch(speedMode)
    {
			  case FREE:{sprintf(tempBuf,"Speed Mode:AUTO");break;}//Ĭ��Ϊ�Զ���
        case MODE1:{sprintf(tempBuf,"Speed Mode:SLOW");break;}//û������ֱ������
				case MODE2:{sprintf(tempBuf,"Speed Mode:MID");break;}//����һ����ֱ������
				case MODE3:{sprintf(tempBuf,"Speed Mode:FAST");break;}//���Ӷ�һ��ֱ������
				case MODE4:{sprintf(tempBuf,"Speed Mode:MOST");break;}//������������
				default:{sprintf(tempBuf,"Speed Mode:ATUO");break;}//Ĭ�Ͼ����Զ���
		}
		setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
		OLED_ShowString(8,2,tempBuf,16);
		//��ʾ�����Ȧ�Ĳ�ֵ
		sprintf(tempBuf,"Valid Def:%d",defaultMax);
	  OLED_ShowString(8,4,tempBuf,16);
		
		
	  //��ʾ�����Ȧ�Ĳ�ֵ
		sprintf(tempBuf,"Coin Def:%d",coinDet);
		OLED_ShowString(8,6,tempBuf,16);
		
		//ȷ�ϰ�ť�Ѿ�����
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


/*��ʾʱ��;���*/
void showTimeAndDistance(void)
{
	  char tempBuf[20] = {0};
		OLED_Clear();
		//��ʾ��ʾ��Ϣ
		sprintf(tempBuf,"TIME:%d S",Time);
		OLED_ShowString(8,0,tempBuf,16);
		
				//��ʾ��ʾ��Ϣ
		sprintf(tempBuf,"Distance:%d CM",count);
		OLED_ShowString(8,10,tempBuf,16);

    //�ٶ���ʾ
    sprintf(tempBuf,"Speed:%5.2f CM/S",(count*1.0/Time*1.0));
		OLED_ShowString(8,30,tempBuf,16);
}
