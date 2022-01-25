#include "ENCODE_SENSOR.h"

// void ENCODING_INIT(ENCODE_SENSOR* SENSOR,ENCODING_OUTPUT_enum LSB_PIN,PIN_enum DIR_PIN){
//     SENSOR->DIR_PIN = DIR_PIN;
//     SENSOR->LSB_PIN = LSB_PIN;
//     ctimer_count_init(SENSOR->LSB_PIN);
//     ctimer_count_clean(SENSOR->LSB_PIN);
//     SENSOR->DIR_PIN = FORWARD;
// }
// ENCODE_RES ENCODING_READ_RESULT(ENCODE_SENSOR* SENSOR){
//     ENCODE_RES RES_SET;
//     RES_SET.speed = ctimer_count_read(SENSOR->LSB_PIN);
//     RES_SET.dir = gpio_read(SENSOR->DIR_PIN);
//     ctimer_count_clean(SENSOR->LSB_PIN);
//     return RES_SET;
// }

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