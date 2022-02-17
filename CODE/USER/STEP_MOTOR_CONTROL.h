#ifndef STEP_MOTOR_CONTROL_H
#define STEP_MOTOR_CONTROL_H

#define ERROR_RANGE 1
#define STEERING_Kp 0.5
#define STEERING_Ki 0.3
#define STEERING_Kd 0.07
#define STEP_MOTOR_MAX_DUTY 5000
#define MOTOR_MAX_PWM(speed) speed + 3000

typedef enum{
    OFF,
    ON
}STATUS_FLAG;

void StepMotorControl_INIT();

int StepMotorControl(int CURRENT_SPEED,int TARGET_SPEED);

#endif