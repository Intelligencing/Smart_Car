#include "EM_SENSOR.h"
#include "zf_adc.h"

int DATA_MAX[4];
int DATA_MIN[4];

void EM_INIT(){
	int i;
    adc_init(ADC_P00,ADC_SYSclk_DIV_10);
    adc_init(ADC_P01,ADC_SYSclk_DIV_10);
    adc_init(ADC_P05,ADC_SYSclk_DIV_10);
    adc_init(ADC_P06,ADC_SYSclk_DIV_10);
	
	for(i=0;i<4;i++){
	DATA_MAX[i]=0;
	DATA_MIN[i]=0;
	}
}

void EM_READ(int* DATA_LIST){
    int i;
    float p;
    
    DATA_LIST[0] = adc_once(ADC_P00,ADC_12BIT);
    DATA_LIST[1] = adc_once(ADC_P01,ADC_12BIT);
    DATA_LIST[2] = adc_once(ADC_P05,ADC_12BIT);
    DATA_LIST[3] = adc_once(ADC_P06,ADC_12BIT);
    /*电感值归一化*/
    for(i=0;i<4;i++){
        if(DATA_LIST[i]>DATA_MAX[i]) DATA_MAX[i]=DATA_LIST[i];
        if(DATA_LIST[i]<DATA_MIN[i]) DATA_MIN[i]=DATA_LIST[i];
    }
    for(i=0;i<4;i++){
        p=(float)(DATA_LIST[i]-DATA_MIN[i])/(float)(DATA_MAX[i]-DATA_MIN[i]);
        DATA_LIST[i]=p*1600; 
    }
}