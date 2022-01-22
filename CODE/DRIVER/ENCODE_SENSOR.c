#include "ENCODE_SENSOR.h"

void ENCODING_INIT(){
    ctimer_count_init(TIMER3_P04);
    ctimer_count_clean(TIMER3_P04);
}
    
uint16 ENCODING_READ_RESULT(){
    uint16 result;
    result=ctimer_count_read(TIMER3_P04);
    ctimer_count_clean(TIMER3_P04);
    return result;
}