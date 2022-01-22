#ifndef SERVO_MOTOR_CONTROL_H
#define SERVO_MOTOR_CONTROL_H

#include"EM_Calc.h"
#include "PID.h"
#include "SERVO_MOTOR.h"

//#define STEPMOTOR_Kp 0.7
//#define STEPMOTOR_Ki 0.3
//#define STEPMOTOR_Kd 0.5

#define STEERING_Kp_0 1
#define STEERING_Ki_0 0
#define STEERING_Kd_0 1
#define STEERING_Kp_1 1
#define STEERING_Ki_1 0
#define STEERING_Kd_1 1

typedef enum{
    ON_STRAIGHT = 0,
    ON_TURN   = 1
}SteeringState;

struct MySteeringPID_params{
    int Kp;
    int Ki;
    int Kd;
};

struct MySteeringPID_params MyParams[2];

PID SERVO_MOTOR_PID;

void MySTEERING_PID_STATE(SteeringState State){
    PID_SET_FACTORS(&SERVO_MOTOR_PID,MyParams[State].Kp,MyParams[State].Ki,MyParams[State].Kd);
}

void SERVO_MOTOR_PID_INIT(){
	  MyParams[0].Kp = STEERING_Kp_0;
    MyParams[0].Ki = STEERING_Ki_0;
    MyParams[0].Kd = STEERING_Kd_0;
    MyParams[1].Kp = STEERING_Kp_1;
    MyParams[1].Ki = STEERING_Ki_1;
    MyParams[1].Kd = STEERING_Kd_1;
    PID_INIT_NEWPID(&SERVO_MOTOR_PID,0,0,0,0,PID_INCREASE_MODE);
	  MySTEERING_PID_STATE(0);
}

float SERVO_MOTOR_CONTROL(int* EM_DATA,int userAngle){
    float CURRENT_INPUT;
    float ANGLE;
    CURRENT_INPUT=EM_CALC_POS_RES(EM_DATA);//接收传入的已经滤波过的电磁信号
	
	  if(userAngle == 0) 
				ANGLE=PID_CALC_RESULT(&SERVO_MOTOR_PID,CURRENT_INPUT);//用PID计算舵机打角
		else 
        ANGLE = userAngle;
		
    SERVO_MOTOR_ANGLE(ANGLE);////输出到舵机
    return ANGLE;//返回摆角
}


#endif