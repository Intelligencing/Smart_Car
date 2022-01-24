#ifndef STEP_MOTOR_CONTROL_H
#define STEP_MOTOR_CONTROL_H

#include "headfile.h"
#include "STEP_MOTOR.h"
#include "PID.h"
#include "LCD_show.h"



typedef enum{
    OFF,
    ON
}STATUS_FLAG;



void STEP_MOTOR_PID_INIT();

int STEP_MOTOR_CONTROL(uint16 CURRENT_SPEED,uint16 TARGET_SPEED);

#endif