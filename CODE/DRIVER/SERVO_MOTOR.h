#ifndef __SERVO_MOTOR_H__
#define __SERVO_MOTOR_H__

/**
 * @description: 初始化伺服电机,使其角度保持在中央(0°)
 * @param NULL
 * @return NULL
 * @example: 
 */
void SERVO_INIT_MOTOR();

/**
 * @description: 设置伺服电机工作角度
 * @param Angle uint8 |Angle|<=10
 * @return *
 * @example: 
 */
void SERVO_SET_ANGLE(float Angle);

/**
 * @description: 逆初始化伺服电机
 * @param *
 * @return *
 * @example: 
 */
void SERVO_DEINIT_MOTOR();

#endif