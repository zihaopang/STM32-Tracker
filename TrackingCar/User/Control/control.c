#include "control.h"

void TackingControl(void)
{	
	  //���Ʊ�־
		if(!Motor.ContorFlag){  return; }
    else{Motor.ContorFlag = 0;}
		//�������־
		if(FOREWARD == Motor.Direction) { MOTOR_FOREWARD; }
    //�����־
		else if(REVERSE == Motor.Direction) { MOTOR_REVERSE; }
    //ֹͣ��־λ
		else if(STOP == Motor.Direction) { MOTOR_STOP; }
	  //���С����ƫ��
    Motor.Distance =  EvmGetPosition();

    //1.�����˶�ģʽ
    if(speedMode == FREE)
		{
        //ͨ��ƫ���������ٶ�
				switch(Motor.Distance)
				{
						case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.9 * RSPEED); break;
						case -3 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.5 * RSPEED); break;
						case -2 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.4 * RSPEED); break;
						case -1 : Motor.LSpeed = -10; Motor.RSpeed = -(uint16_t)(0.3 * RSPEED); break;
						case  0 : Motor.LSpeed = 0; Motor.RSpeed = 0; break;
						case  1 : Motor.LSpeed = -(uint16_t)(0.3 * RSPEED); Motor.RSpeed = -10; break;
						case  2 : Motor.LSpeed = -(uint16_t)(0.4 * RSPEED); Motor.RSpeed = 0; break;
						case  3 : Motor.LSpeed = -(uint16_t)(0.5 * RSPEED); Motor.RSpeed = 0; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.9 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
    }
		//2.����220 ��ͨ��
		else if(speedMode == MODE1)
		{
			  		//ͨ��ƫ���������ٶ�
				switch(Motor.Distance)
				{
						case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.8 * RSPEED); break;
						case -3 : Motor.LSpeed = 0; Motor.RSpeed = -95; break;
						case -2 : Motor.LSpeed = 0; Motor.RSpeed = -66; break;
						case -1 : Motor.LSpeed = -10; Motor.RSpeed = -66; break;
						case  0 : Motor.LSpeed = 0; Motor.RSpeed = 0; break;
						case  1 : Motor.LSpeed = -66; Motor.RSpeed = -10; break;
						case  2 : Motor.LSpeed = -66; Motor.RSpeed = 0; break;
						case  3 : Motor.LSpeed = -95; Motor.RSpeed = 0; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.8 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
		}
		//3.����220 ֱ�߼���һ��������
		else if(speedMode == MODE2)
		{
			  switch(Motor.Distance)
				{
					  case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.8 * RSPEED); break;
						case -3 : Motor.LSpeed = 30; Motor.RSpeed = -95; break;
						case -2 : Motor.LSpeed = 0; Motor.RSpeed = -66; break;
						case -1 : Motor.LSpeed = -10; Motor.RSpeed = -66; break;
					
						case  0 : Motor.LSpeed = 80; Motor.RSpeed = 80; break;
					
						case  1 : Motor.LSpeed = -66; Motor.RSpeed = -10; break;
						case  2 : Motor.LSpeed = -66; Motor.RSpeed = 0; break;
						case  3 : Motor.LSpeed = -95; Motor.RSpeed = 30; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.8 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
    }
		//4.��������Ϊ220��ֱ������ 
		else if(speedMode == MODE3)
 		{
			  		//ͨ��ƫ���������ٶ�
				switch(Motor.Distance)
				{
            case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.8 * RSPEED); break;
						case -3 : Motor.LSpeed = 30; Motor.RSpeed = -95; break;
						case -2 : Motor.LSpeed = 80; Motor.RSpeed = 15; break;
						case -1 : Motor.LSpeed = 60; Motor.RSpeed = 20; break;
					
						case  0 : Motor.LSpeed = 120; Motor.RSpeed = 120; break;
					
						case  1 : Motor.LSpeed = 20; Motor.RSpeed = 60; break;
						case  2 : Motor.LSpeed = 15; Motor.RSpeed = 80; break;
						case  3 : Motor.LSpeed = -95; Motor.RSpeed = 30; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.8 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
    }
		//5.��������Ϊ220�������������
		else if(speedMode == MODE4)
 		{
			  		//ͨ��ƫ���������ٶ�+
				switch(Motor.Distance)
				{
            case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.8 * RSPEED); break;
						case -3 : Motor.LSpeed = 30; Motor.RSpeed = -95; break;
						case -2 : Motor.LSpeed = 80; Motor.RSpeed = 15; break;
						case -1 : Motor.LSpeed = 60; Motor.RSpeed = 20; break;
					
						case  0 : Motor.LSpeed = 100; Motor.RSpeed = 100; break;
					
						case  1 : Motor.LSpeed = 20; Motor.RSpeed = 60; break;
						case  2 : Motor.LSpeed = 15; Motor.RSpeed = 80; break;
						case  3 : Motor.LSpeed = -95; Motor.RSpeed = 30; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.8 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
    }
		else //���������ȫ����ͳһ�ķ�ʽ��PWM��Ϊ�������
		{
			  		//ͨ��ƫ���������ٶ�
				switch(Motor.Distance)
				{
						case -4 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.9 * RSPEED); break;
						case -3 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.5 * RSPEED); break;
						case -2 : Motor.LSpeed = 0; Motor.RSpeed = -(uint16_t)(0.4 * RSPEED); break;
						case -1 : Motor.LSpeed = -10; Motor.RSpeed = -(uint16_t)(0.3 * RSPEED); break;
						case  0 : Motor.LSpeed = 0; Motor.RSpeed = 0; break;
						case  1 : Motor.LSpeed = -(uint16_t)(0.3 * RSPEED); Motor.RSpeed = -10; break;
						case  2 : Motor.LSpeed = -(uint16_t)(0.4 * RSPEED); Motor.RSpeed = 0; break;
						case  3 : Motor.LSpeed = -(uint16_t)(0.5 * RSPEED); Motor.RSpeed = 0; break;
						case  4 : Motor.LSpeed = -(uint16_t)(0.9 * LSPEED); Motor.RSpeed = 0; break;
						default : break;
				}
    }
		
		SetSpeed(Motor.LSpeed,Motor.RSpeed);
}


/*�ж���ֹλ��*/
void compareDistance()
{
		char buf[50];
	
	  count = (TIM_GetCounter(TIM2) +  TIM_GetCounter(TIM1)) / 2;//ȡ��������������ƽ��ֵ 
	  
	  if(count >= endDistance)
		{
				MOTOR_STOP;//���ֹͣ
				TIM_Cmd(TIM3, DISABLE);
				showTimeAndDistance();
				SysTickDisable();
				
			  OLED_Clear();
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


