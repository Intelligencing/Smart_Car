#include "EM_SENSOR.h"
#include "zf_adc.h"

void EM_SENSOR_INIT(){
    adc_init(ADC_P00,ADC_SYSclk_DIV_10);
    adc_init(ADC_P01,ADC_SYSclk_DIV_10);
    adc_init(ADC_P05,ADC_SYSclk_DIV_10);
    adc_init(ADC_P06,ADC_SYSclk_DIV_10);
}

void EM_READ_SENSOR(int* DATA_LIST){
    DATA_LIST[0] = adc_once(ADC_P00,ADC_12BIT);
    DATA_LIST[1] = adc_once(ADC_P01,ADC_12BIT);
    DATA_LIST[2] = adc_once(ADC_P05,ADC_12BIT);
    DATA_LIST[3] = adc_once(ADC_P06,ADC_12BIT);
}