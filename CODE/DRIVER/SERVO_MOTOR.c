#include "SERVO_MOTOR.h"
#include "zf_delay.h"
#include "zf_pwm.h"

#define SERVO_OUTPUT PWMB_CH1_P74

#define MAX_ANGLE 9

void SERVO_INIT_MOTOR(){
    pwm_init(SERVO_OUTPUT,50,770);
}

void SERVO_SET_ANGLE(float Angle){
    uint16 DUTY;
    if(Angle>MAX_ANGLE) Angle = MAX_ANGLE;
    if(Angle<-MAX_ANGLE) Angle = -MAX_ANGLE;
    DUTY = (Angle*30);
    pwm_duty(SERVO_OUTPUT,770+DUTY);
    delay_ms(30);
}