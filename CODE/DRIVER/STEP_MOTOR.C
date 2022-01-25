/*
 * @Description  : 步进电机控制实现
 * @Author       : FZU Liao
 * @Date         : 2022-01-03 15:48:25
 * @LastEditors  : Liao
 * @LastEditTime : 2022-01-15 23:14:28
 * @FilePath     : \Driver\STEP_MOTOR.c
 * Copyright 2022 FZU Liao, All Rights Reserved. 
 */

//步进电机控制芯片HIP4082真值表
/*———————————————————————————————————————————————————————
 |  | ALI | BLI |   | ALO | AHO | BLO | BHO | |  STATE  |
 |  ————————————————————————————————————————— | ——————— |
 |  |  1  |  0  |   |  1  |  0  |  0  |  1  | | FORWARD |
 |  ————————————————————————————————————————— | ——————— |
 |  |  0  |  1  |   |  0  |  1  |  1  |  0  | |   BACK  |
 |  ————————————————————————————————————————— | ——————— |
 |  |  1  |  1  |   |  1  |  0  |  1  |  0  | |   STOP  | 
 |  ————————————————————————————————————————— | ——————— |
 |  |  0  |  0  |   |  0  |  1  |  0  |  1  | |   NULL  |
————————————————————————————————————————————————————————*/

#include "STEP_MOTOR.h"
#include "zf_delay.h"

#define MOTOR_FREQUENCY 17000
#define MOTOR_MAX_DUTY  4000

void STEP_MOTOR_INIT(STEP_MOTOR* MOTOR,STEP_MOTOR_CHANNEL ALI,STEP_MOTOR_CHANNEL BLI,PIN_enum GPIO_Pin_ALI,PIN_enum GPIO_PIN_BLI){
    gpio_mode(GPIO_Pin_ALI,GPO_PP);
    gpio_mode(GPIO_PIN_BLI,GPO_PP);
    MOTOR->ALI = ALI;
    MOTOR->BLI = BLI;
    MOTOR->CURRENT_PWM_DUTY = 0;
    pwm_init(ALI,MOTOR_FREQUENCY,0);       
    pwm_init(BLI,MOTOR_FREQUENCY,0);  
}

void STEP_MOTOR_FORWARD(STEP_MOTOR* MOTOR,int Duty){
    MOTOR->CURRENT_PWM_DUTY = Duty;
    pwm_duty(MOTOR->ALI,Duty);
    pwm_duty(MOTOR->BLI,0);
}

void STEP_MOTOR_STOP(STEP_MOTOR* MOTOR){
    pwm_duty(MOTOR->ALI,1000);
    pwm_duty(MOTOR->BLI,1000);
}

void STEP_MOTOR_BACK(STEP_MOTOR* MOTOR,int Duty){
    MOTOR->CURRENT_PWM_DUTY = Duty;
    pwm_duty(MOTOR->ALI,0);
    pwm_duty(MOTOR->BLI,Duty);
}

uint32 STEP_MOTOR_GET_DUTY(STEP_MOTOR* MOTOR){
    return MOTOR->CURRENT_PWM_DUTY;
}

