#include "data.h"

uint8_t speedMode = FREE;//�����������������ģʽ

//ͨ��ģʽ�������ٶȣ���ȷ�ϰ�ť���µ���һ����һ��
void setSpeedByMode(void)
{
	  if(speedMode != FREE)//��������Զ�ģʽ
		{
			  //������������Ļ����ٶȣ������������׼�������ٶ�
			  LSPEED = 220;
			  RSPEED = 220;
		}
}
