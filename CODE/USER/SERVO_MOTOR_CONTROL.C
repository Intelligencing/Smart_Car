#include "SERVO_MOTOR_CONTROL.h"
#include"EM_Calc.h"
#include "PID.h"
#include "SERVO_MOTOR.h"
#include "LCD_show.h"

struct MySteeringPID_params MyParams[2];

PID MySTEERING_PID;

float ANGLE_ADAPTER(float WHEEL_ANGLE){
    float Steering_ANGLE;
    Steering_ANGLE = WHEEL_ANGLE*0.23333;
    if(Steering_ANGLE>7) Steering_ANGLE = 7;
    if(Steering_ANGLE<-7) Steering_ANGLE = -7;
    return Steering_ANGLE;
}

void MySteeringPIDAdapter_State(SteeringState State){
    PID_SET_FACTORS(&MySTEERING_PID,MyParams[State].Kp,MyParams[State].Ki,MyParams[State].Kd);
}

void MySteeringControl_INIT(){
	  SERVO_INIT_MOTOR();
    MyParams[0].Kp = STEERING_Kp_0;
    MyParams[0].Ki = STEERING_Ki_0;
    MyParams[0].Kd = STEERING_Kd_0;
    MyParams[1].Kp = STEERING_Kp_1; 
    MyParams[1].Ki = STEERING_Ki_1;
    MyParams[1].Kd = STEERING_Kd_1;
    MyParams[2].Kp = STEERING_Kp_2; 
    MyParams[2].Ki = STEERING_Ki_2;
    MyParams[2].Kd = STEERING_Kd_2;
    MyParams[3].Kp = STEERING_Kp_3; 
    MyParams[3].Ki = STEERING_Ki_3;
    MyParams[3].Kd = STEERING_Kd_3;
    PID_INIT_NEWPID(&MySTEERING_PID,0,0,0,0,PID_INCREASE_MODE);
  	MySteeringPIDAdapter_State(ON_STRAIGHT);
}

void MySteeringControl_TASK(float ANGLE){
    SERVO_SET_ANGLE(ANGLE_ADAPTER(ANGLE));//利用电磁信号计算舵机大致摆角（调用PIDadapter算ERROR与目标值）
}

float MySteeringControl_GETANGLE(int* EM_DATA,int userAngle){
    float CURRENT_INPUT;
    float ANGLE;
    CURRENT_INPUT = EM_CALC_POS_RES(EM_DATA)*1000;
    if(userAngle == 0) 
        ANGLE = PID_CALC_RESULT(&MySTEERING_PID,CURRENT_INPUT);
    else 
        ANGLE = userAngle;
        return ANGLE;//返回摆角
}
