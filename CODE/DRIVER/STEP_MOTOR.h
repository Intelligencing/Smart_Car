/**
 *@description :步进电机控制
 *@author HQU zeng
 *@date 2022/1/14 21:49
 *@LastEditors:Zeng
 *@LastEdit Time:
 *@FilePath:C:\Users\123456\Desktop\SMARTER CAR\CODE\DRIVER\STEP_MOTOR_H
 *@copyright 2022 FZU Liao,ALL Rights Reserved.
 */

#ifndef STEP_MOTOR_H
#define STEP_MOTOR_H
#include "zf_pwm.h"
#define PWM_CHANNEL_ALI PWMA_CH1P_P60
#define PWM_CHANNEL_BLI PWMA_CH3P_P64

typedef enum {
    STEP_MOTOR_P60 = PWMA_CH1P_P60,
    STEP_MOTOR_P62 = PWMA_CH2P_P62,
    STEP_MOTOR_P64 = PWMA_CH3P_P64,
    STEP_MOTOR_P66 = PWMA_CH4P_P66
} STEP_MOTOR_CHANNEL;

struct STEP_MOTOR_STRUCT {
    STEP_MOTOR_CHANNEL ALI;
    STEP_MOTOR_CHANNEL BLI;
    int CURRENT_PWM_DUTY;
};

typedef struct STEP_MOTOR_STRUCT STEP_MOTOR;

void STEP_MOTOR_INIT();

void STEP_MOTOR_STOP();

void STEP_MOTOR_FORWORD(int duty);
 
void STEP_MOTOR_BACKWARD(int duty);

uint32 STEP_MOTOR_GET_DUTY(STEP_MOTOR* MOTOR);

#endif