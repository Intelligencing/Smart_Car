#ifndef SERVO_MOTOR_CONTROL_H
#define SERVO_MOTOR_CONTROL_H
//0.115
#define STEERING_Kp_0 0.115
#define STEERING_Ki_0 0
#define STEERING_Kd_0 0.03
#define STEERING_Kp_1 0.16
#define STEERING_Ki_1 0
#define STEERING_Kd_1 0.03
#define STEERING_Kp_2 0.16
#define STEERING_Ki_2 0
#define STEERING_Kd_2 0.03
#define STEERING_Kp_3 0.03
#define STEERING_Ki_3 0
#define STEERING_Kd_3 0.03

typedef enum{
    ON_STRAIGHT = 0,
    ON_TURN   = 1
}SteeringState;

struct SteeringPID_params{
    float Kp;
    float Ki;
    float Kd;
};

float ANGLE_ADAPTER(float WHEEL_ANGLE);

void SteeringPID_State(SteeringState State);

void SteeringControl_INIT();

void SteeringControl(float ANGLE);

float ANGLE_GETANGLE(int* EM_DATA,int userAngle);


#endif