#ifndef SERVO_MOTOR_CONTROL_H
#define SERVO_MOTOR_CONTROL_H

#include"EM_Calc.h"
#include "PID.h"
#include "SERVO_MOTOR.h"
#include "LCD_show.h"

typedef enum{
    ON_STRAIGHT = 0,
    ON_TURN   = 1
}SteeringState;

struct MySteeringPID_params{
    int Kp;
    int Ki;
    int Kd;
};

//struct MySteeringPID_params MyParams[2];

float ANGLE_ADAPTER(float WHEEL_ANGLE);

void MySTEERING_PID_STATE(SteeringState State);

void SERVO_MOTOR_PID_INIT();

float SERVO_MOTOR_CONTROL(int* EM_DATA,int userAngle);


#endif