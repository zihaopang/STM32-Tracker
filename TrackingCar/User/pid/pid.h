#ifndef __PID_H
#define __PID_H
	
#include "data.h"

typedef struct{
		float p;
		float i;
		float d;
		
		float desire;
		float error;
		float last_error;
		float pre_error;
		
		float integ;
		float deriv;
		
		float p_out;
		float i_out;
		float d_out;
		
		float i_limit;
	
}PID;

extern PID SpeedPid;
extern PID AnglePid;

extern void pid_init(PID* pid, float kp, float ki, float kd, float limit);
extern float pid_update(PID* pid, float desire, float measure, float dt);
extern float Inc_pid_updata(PID* pid, float desire ,float measure, float dt);
extern void pid_settings(void);

#endif



