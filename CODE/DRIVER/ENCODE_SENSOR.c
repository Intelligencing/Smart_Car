#include "ENCODE_SENSOR.h"

void ENCODING_INIT(){
    ctimer_count_init(TIM_0);
    ctimer_count_clean(TIM_0);
}
    
uint16 ENCODING_READ_RESULT(){
    uint16 result;
    result=ctimer_count_read(TIM_0);
    ctimer_count_clean(TIM_0);
    return result;
}