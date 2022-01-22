#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include "zf_pwm.h"

#define PWM_CHANNEL_SERVO PWMB_CH1_P74



void SERVO_MOTOR_INIT();

void SERVO_MOTOR_ANGLE(int angle);



#endif