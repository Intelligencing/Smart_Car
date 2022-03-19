#include "SERVO_MOTOR_CONTROL.h"
#include "EM_Calc.h"
#include "PID.h"
#include "SERVO_MOTOR.h"
#include "LCD_show.h"

struct SteeringPID_params Params[4];
float LAST_ERROR;
PID STEERING_PID;

float ANGLE_ADAPTER(float WHEEL_ANGLE){
    float Steering_ANGLE;
    Steering_ANGLE = WHEEL_ANGLE*0.233333;//0.233333
    if(Steering_ANGLE>9) Steering_ANGLE = 9;
    if(Steering_ANGLE<-9) Steering_ANGLE = -9;
    return Steering_ANGLE;
}

void SteeringPID_State(SteeringState State){
    PID_SET_FACTORS(&STEERING_PID,Params[State].Kp,Params[State].Ki,Params[State].Kd);
}

void SteeringControl_INIT(){
	SERVO_INIT_MOTOR();
    Params[0].Kp = STEERING_Kp_0;
    Params[0].Ki = STEERING_Ki_0;
    Params[0].Kd = STEERING_Kd_0;
    Params[1].Kp = STEERING_Kp_1; 
    Params[1].Ki = STEERING_Ki_1;
    Params[1].Kd = STEERING_Kd_1;
    Params[2].Kp = STEERING_Kp_2; 
    Params[2].Ki = STEERING_Ki_2;
    Params[2].Kd = STEERING_Kd_2;
    Params[3].Kp = STEERING_Kp_3; 
    Params[3].Ki = STEERING_Ki_3;
    Params[3].Kd = STEERING_Kd_3;
    PID_INIT_NEWPID(&STEERING_PID,0,0,0,0,PID_REALIZE_MODE);
  	SteeringPID_State(ON_STRAIGHT);
} 

void SteeringControl(float ANGLE){
    SERVO_SET_ANGLE(ANGLE_ADAPTER(ANGLE));//利用电磁信号计算舵机大致摆角（调用PIDadapter算ERROR与目标值）
}

float ANGLE_GETANGLE(int* EM_DATA,float userAngle,float Kp,float Ki,float Kd){
    float CURRENT_INPUT;
    float ANGLE;
//    CURRENT_INPUT = 0;
//    ANGLE = 0;
    CURRENT_INPUT = EM_CALC_POS_RES(EM_DATA);
	if (CURRENT_INPUT<0) CURRENT_INPUT=-CURRENT_INPUT*CURRENT_INPUT;
	else CURRENT_INPUT=CURRENT_INPUT*CURRENT_INPUT;
    if(userAngle == 0){
        Ki= Ki-CURRENT_INPUT;
        //ANGLE = PID_CALC_RESULT(&STEERING_PID,CURRENT_INPUT); 
		ANGLE = -Kp*CURRENT_INPUT-Ki*CURRENT_INPUT+Kd*(-CURRENT_INPUT-LAST_ERROR);//
			//LCD  ("I",Ki*CURRENT_INPUT,6);
			LCD("D",Kd*(-CURRENT_INPUT-LAST_ERROR),7);
		LAST_ERROR = -CURRENT_INPUT;	
    }       
    else 
        ANGLE = userAngle;//强制打角
        return ANGLE;//返回摆角
}
