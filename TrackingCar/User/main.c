#include "data.h"
#include "sys.h"

uint32_t count = 0;//��������
uint32_t endDistance = 715;//С������ʱ���н�����
/*�ṩ��OLED����*/
uint16_t defaultMax  = 5;//LDC��Ч��ֵ
uint16_t coinDet = 120;//��⵽Ӳ�ҵĲ�ֵ

void SysInit(void)
{
	  SysTickInit();									//�δ�ʱ����ʼ��
		LED_Init();											//Led�Ƴ�ʼ��PA8
	  beepInit();                     //��ʼ���������
	  EncoderInit();									//��������ʼ��
	  OLED_Init();										//OLED�����ʼ��
	  KEY_Init();										//������ʼ��
    MotorPwmOutputInit();						//���pwm�����ʼ��PB4  PB5
	  MotorInit();										//������ƶ˿ڳ�ʼ��,���Ƶ����,��,ͣ(TB6612��ANI1,AN2)
    while(!EvmInit());              //LDC1314��ʼ��
}

int main(void)
{
		SysInit();
	  LED0 = !LED0;
	  oledStartInfo();//��ʾ��ʼ����Ϣ�Լ��Ƿ��ʼ�ɹ�
	
	  while(1)
		{
		    setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
			  changKeyMenu();
			
			  DelayMs(10);
			  setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
			  if(showMainMenu() == YES)
			  {
					  setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
					  break;
				}
				setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
		}
	
	  setSpeedByMode();//ͨ�����õ�ģʽ������ʼ���ţ�ʵʱˢ����ȥ
		DelayMs(1000);//��ʱһ�뿪ʼ�˶�
		count = 0;//�Ѽ����������
	  SysTickEnable();
		LED0 = !LED0;
		
		while(1)
		{
			  //ѭ������
				TackingControl();
			  //�ȽϾ����յ��λ��
			  compareDistance();
			  //��ʾOLED��ʾ��Ϣ
			  if(showOledFlag == YES)
				{
					  showOledFlag = NO;
			      showTimeAndDistance();
				}
				//��ͣ��ť
				quickStopKey();
				
		}
}


