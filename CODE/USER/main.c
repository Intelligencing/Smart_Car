#include "headfile.h"
#include "ENCODE_SENSOR.h"

void SYS_INIT_ALL(){
    sys_clk=30000000;
    board_init();
    lcd_init();
    ISR_INIT();
    EnableGlobalIRQ();
    
}

void main(){
    SYS_INIT_ALL();
    while(1){

    }
}