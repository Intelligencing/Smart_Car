#include "SERVO_MOTOR_CONTROL.h"

//#define STEPMOTOR_Kp 0.7
//#define STEPMOTOR_Ki 0.3
//#define STEPMOTOR_Kd 0.5

#define STEERING_Kp_0 0.1
#define STEERING_Ki_0 0
#define STEERING_Kd_0 0.1
#define STEERING_Kp_1 0.1
#define STEERING_Ki_1 0
#define STEERING_Kd_1 0.1

struct MySteeringPID_params MyParams[2];

PID SERVO_MOTOR_PID;

float ANGLE_ADAPTER(float WHEEL_ANGLE){
    float Steering_ANGLE;
    Steering_ANGLE = WHEEL_ANGLE*0.22;
    if(Steering_ANGLE>7) Steering_ANGLE = 7;
    if(Steering_ANGLE<-7) Steering_ANGLE = -7;
    return Steering_ANGLE;
}

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
    float res;
    CURRENT_INPUT=EM_CALC_POS_RES(EM_DATA);//接收传入的已经滤波过的电磁信号
	//利用电磁信号计算舵机大致摆角（调用PIDadapter算ERROR与目标值）
    if(userAngle == 0) 
        if(CURRENT_INPUT>300||CURRENT_INPUT<-300) ANGLE = PID_CALC_RESULT(&SERVO_MOTOR_PID,CURRENT_INPUT);
    else 
        ANGLE = userAngle;
    //输出到舵机
    SERVO_MOTOR_ANGLE(ANGLE_ADAPTER(ANGLE));
    //返回摆角
    res = PID_CALC_RESULT(&SERVO_MOTOR_PID,CURRENT_INPUT);
    LCD_display("in",CURRENT_INPUT,6);
    LCD_display("res",res,7);
    
    return ANGLE;//返回摆角
}
