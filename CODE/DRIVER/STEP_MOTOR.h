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
#include "zf_gpio.h"

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

/**
 * @description: 初始化步进电机
 * @param MOTOR STEP_MOTOR*
 * @param ALI STEP_MOTOR_CHANNEL
 * @param BLI STEP_MOTOR_CHANNEL
 * @param GPIO_Pin_ALI PIN_enum
 * @param GPIO_PIN_BLI PIN_enum
 * @return *
 * @example: 
 */
void STEP_MOTOR_INIT(STEP_MOTOR* MOTOR,STEP_MOTOR_CHANNEL ALI,STEP_MOTOR_CHANNEL BLI,PIN_enum GPIO_Pin_ALI,PIN_enum GPIO_PIN_BLI);

/**
 * @description: 步进电机前进
 * @param MOTOR STEP_MOTOR*
 * @param Duty int
 * @return *
 * @example: 
 */
void STEP_MOTOR_FORWARD(STEP_MOTOR* MOTOR,int Duty);

/**
 * @description: 步进电机刹车
 * @param MOTOR STEP_MOTOR*
 * @return *
 * @example: 
 */
void STEP_MOTOR_STOP(STEP_MOTOR* MOTOR);

/**
 * @description: 步进电机后退
 * @param MOTOR STEP_MOTOR*
 * @param Duty int
 * @return *
 * @example: 
 */
void STEP_MOTOR_BACK(STEP_MOTOR* MOTOR,int Duty);

/**
 * @description: 读取电机占空比
 * @param MOTOR STEP_MOTOR*
 * @return *
 * @example:
 */
uint32 STEP_MOTOR_GET_DUTY(STEP_MOTOR* MOTOR);

#endif