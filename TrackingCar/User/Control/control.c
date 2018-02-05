#include "control.h"

void TackingControl(void)
{	
	  //控制标志
		if(!Motor.ContorFlag){  return; }
    else{Motor.ContorFlag = 0;}
		//正向方向标志
		if(FOREWARD == Motor.Direction) { MOTOR_FOREWARD; }
    //反向标志
		else if(REVERSE == Motor.Direction) { MOTOR_REVERSE; }
    //停止标志位
		else if(STOP == Motor.Direction) { MOTOR_STOP; }
	  //获得小车的偏移
    Motor.Distance =  EvmGetPosition();

    //1.自由运动模式
    if(speedMode == FREE)
		{
        //通过偏移来控制速度
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
		//2.油门220 普通的
		else if(speedMode == MODE1)
		{
			  		//通过偏移来控制速度
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
		//3.油门220 直线加速一部分油门
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
		//4.基础油门为220，直线增速 
		else if(speedMode == MODE3)
 		{
			  		//通过偏移来控制速度
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
		//5.基础油门为220，增加最大油门
		else if(speedMode == MODE4)
 		{
			  		//通过偏移来控制速度+
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
		else //其他情况，全部以统一的方式给PWM，为错误情况
		{
			  		//通过偏移来控制速度
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


/*判断终止位置*/
void compareDistance()
{
		char buf[50];
	
	  count = (TIM_GetCounter(TIM2) +  TIM_GetCounter(TIM1)) / 2;//取出两个编码器的平均值 
	  
	  if(count >= endDistance)
		{
				MOTOR_STOP;//马达停止
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


