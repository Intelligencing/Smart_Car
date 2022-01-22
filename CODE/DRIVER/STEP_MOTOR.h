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
/**
 * @discription :步进电机初始化
 * @param STEP_MOTOR_CHANNEL
 * @param PWM_CHANNEL_ALI
 * @param PWM_CHANNEL_BLI
 * @return NULL
 * @example:
 */
void STEP_MOTOR_INIT();

void STEP_MOTOR_STOP();

void STEP_MOTOR_FORWORD(int duty);
 
void STEP_MOTOR_BACKWARD(int duty);



#endif