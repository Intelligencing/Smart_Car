#ifndef ENCODE_SENSOR_H
#define ENCODE_SENSPR_H

#include "zf_tim.h"

typedef enum{
    TIMER0_P34 = TIM_0,
    TIMER1_P35 = TIM_1,
    TIMER2_P54 = TIM_2,
    TIMER3_P04 = TIM_3,
    TIMER4_P06 = TIM_4
}ENCODING_OUTPUT_enum;

typedef enum{
    FORWARD  = 1,
    BACKWARD = 0
}Direction;

void ENCODING_INIT();

uint16 ENCODING_READ_RESULT();

#endif