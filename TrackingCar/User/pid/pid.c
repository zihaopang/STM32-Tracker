#include "pid.h"

PID SpeedPid;
PID AnglePid;

//初始化pid的参数
void pid_init(PID* pid, float kp, float ki, float kd, float limit)
{
		pid->p = kp;
		pid->i = ki;
		pid->d = kd;
		pid->i_limit = limit;
}

float pid_update(PID* pid, float desire, float measure, float dt)
{
		float result;
		pid->desire = desire;																						//期望值赋值，内环以外环的输出作为期望值
		pid->error = pid->desire - measure;

		pid->integ += pid->error * dt;																	//求积分

		if(pid->integ > pid->i_limit)	pid->integ = pid->i_limit;				//积分限定
		if(pid->integ < -pid->i_limit)	pid->integ = -pid->i_limit;

		pid->deriv = (pid->error - pid->pre_error) * 1.0f / dt;

		pid->p_out = pid->error * pid->p;
		pid->i_out = pid->integ * pid->i;
		pid->d_out = pid->deriv * pid->d;

		result = pid->p_out + pid->i_out + pid->d_out;
		pid->pre_error = pid->error;																		//更新误差
		
		return result;
}

float Inc_pid_updata(PID* pid, float desire, float measure, float dt)
{
		float ilncpid;
		
		pid->desire = desire;	
		pid->error = pid->desire - measure;
	
		pid->integ = pid->error * dt;
		pid->deriv = ((pid->error - pid->last_error) - (pid->last_error - pid->pre_error)) * 1.0f / dt;
		
		pid->p_out = (pid->error - pid->last_error) * pid->p;
		pid->i_out = pid->integ * pid->i;
		pid->d_out = pid->deriv * pid->d;
	
		ilncpid = pid->p_out - pid->i_out + pid->d_out;
	
		pid->last_error = pid->error;
		pid->pre_error = pid->last_error;
	
		return ilncpid;
}

void pid_settings(void)
{
		pid_init(&SpeedPid, 1.9, 0, 0.7, 0);
		pid_init(&AnglePid, 0.7, 0, 0.5, 0);
}















