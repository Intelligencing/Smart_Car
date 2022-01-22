#include "zf_gpio.h"
#include "SERVO_MOTOR.h"
#include "zf_delay.h"

#define MAX_ANGLE 10

void SERVO_MOTOR_INIT(){
    pwm_init(PWM_CHANNEL_SERVO,50,760);
}
   
void SERVO_MOTOR_ANGLE(int angle){
    uint16 duty;
    if(angle>MAX_ANGLE) angle = MAX_ANGLE;
    if(angle<-MAX_ANGLE) angle = -MAX_ANGLE;
    duty=angle*30;
    pwm_duty(PWM_CHANNEL_SERVO,760+duty);
    delay_ms(30);
}