#ifndef SERVO_MOTOR_CONTROL_H
#define SERVO_MOTOR_CONTROL_H



#define STEERING_Kp_0 0.09
#define STEERING_Ki_0 0
#define STEERING_Kd_0 0.03
#define STEERING_Kp_1 0.3
#define STEERING_Ki_1 0
#define STEERING_Kd_1 0.03
#define STEERING_Kp_2 0.5
#define STEERING_Ki_2 0
#define STEERING_Kd_2 0.1
#define STEERING_Kp_3 0.7
#define STEERING_Ki_3 0
#define STEERING_Kd_3 0.1

typedef enum{
    ON_STRAIGHT = 0,
    ON_TURN   = 1
}SteeringState;

struct MySteeringPID_params{
    int Kp;
    int Ki;
    int Kd;
};

float ANGLE_ADAPTER(float WHEEL_ANGLE);

void MySteeringPIDAdapter_State(SteeringState State);

void MySteeringControl_INIT();

void MySteeringControl_TASK(float ANGLE);

float MySteeringControl_GETANGLE(int* EM_DATA,int userAngle);


#endif