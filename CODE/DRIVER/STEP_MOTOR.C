#include "STEP_MOTOR.H"
#include "zf_gpio.h"
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

#define MOTOR_FREQUENCY 17000
#define MOTOR_MAX_DUTY  4000

void STEP_MOTOR_INIT(){
    pwm_init(PWM_CHANNEL_ALI,12500,0);
    pwm_init(PWM_CHANNEL_BLI,12500,0);
    gpio_mode(P6_0,GPO_PP);
    gpio_mode(P6_4,GPO_PP);
}
    
void STEP_MOTOR_STOP(){
    pwm_duty(PWM_CHANNEL_ALI,0);
    pwm_duty(PWM_CHANNEL_BLI,0);
}
    
void STEP_MOTOR_FORWORD(int duty){
    pwm_duty(PWM_CHANNEL_ALI,duty); 
    pwm_duty(PWM_CHANNEL_BLI,0);
    
}
 
void STEP_MOTOR_BACKWARD(int duty){
    pwm_duty(PWM_CHANNEL_ALI,0); 
    pwm_duty(PWM_CHANNEL_BLI,duty);
}
