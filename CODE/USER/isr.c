#include "isr.h"

struct FUNC_CONTAINER{
    void (*func)();
};

struct FUNC_CONTAINER FUNCLIST[27];

void ISR_INIT(){
    int i;
    for(i=0;i<27;i++){
        FUNCLIST[i].func=0;
    }
}

void SET_ISR_FUNC(ISR_TYPE Isr,void (*func)()){
    FUNCLIST[Isr].func = func;
}

void  INT0_Isr()  interrupt 0{
    if(FUNCLIST[0].func!=0)
        (*FUNCLIST[0].func)();
}
void  TM0_Isr()   interrupt 1{
    if(FUNCLIST[1].func!=0)
        (*FUNCLIST[1].func)();
}
void  INT1_Isr()  interrupt 2{
    if(FUNCLIST[2].func!=0)
        (*FUNCLIST[2].func)();
}
void  TM1_Isr()   interrupt 3{
    if(FUNCLIST[3].func!=0)
        (*FUNCLIST[3].func)();
}
void  UART1_Isr() interrupt 4{
    if(FUNCLIST[4].func!=0)
        (*FUNCLIST[4].func)();
}
void  ADC_Isr()   interrupt 5{
    if(FUNCLIST[5].func!=0)
        (*FUNCLIST[5].func)();
}
void  LVD_Isr()   interrupt 6{
    if(FUNCLIST[6].func!=0)
        (*FUNCLIST[6].func)();
}
void  PCA_Isr()   interrupt 7{
    if(FUNCLIST[7].func!=0)
        (*FUNCLIST[7].func)();
}
void  UART2_Isr() interrupt 8{
    if(FUNCLIST[8].func!=0)
        (*FUNCLIST[8].func)();
}
void  SPI_Isr()   interrupt 9{
    if(FUNCLIST[9].func!=0)
        (*FUNCLIST[9].func)();
}
void  INT2_Isr()  interrupt 10{
    if(FUNCLIST[10].func!=0)
        (*FUNCLIST[10].func)();
}
void  INT3_Isr()  interrupt 11{
    if(FUNCLIST[11].func!=0)
        (*FUNCLIST[11].func)();
}
void  TM2_Isr()   interrupt 12{
    if(FUNCLIST[12].func!=0)
        (*FUNCLIST[12].func)();
}
void  INT4_Isr()  interrupt 16{
    if(FUNCLIST[16].func!=0)
        (*FUNCLIST[16].func)();
}
void  UART3_Isr() interrupt 17{
    if(FUNCLIST[17].func!=0)
        (*FUNCLIST[17].func)();
}
void  UART4_Isr() interrupt 18{
    if(FUNCLIST[18].func!=0)
        (*FUNCLIST[18].func)();
}
void  TM3_Isr()   interrupt 19{
    if(FUNCLIST[19].func!=0)
        (*FUNCLIST[19].func)();
}
void  TM4_Isr()   interrupt 20{
    if(FUNCLIST[20].func!=0)
        (*FUNCLIST[20].func)();
}
void  CMP_Isr()   interrupt 21{
    if(FUNCLIST[21].func!=0)
        (*FUNCLIST[21].func)();
}
void  I2C_Isr()   interrupt 24{
    if(FUNCLIST[24].func!=0)
        (*FUNCLIST[24].func)();
}
void  USB_Isr()   interrupt 25{
    if(FUNCLIST[25].func!=0)
        (*FUNCLIST[25].func)();
}
void  PWM1_Isr()  interrupt 26{
    if(FUNCLIST[26].func!=0)
        (*FUNCLIST[26].func)();
}
void  PWM2_Isr()  interrupt 27{
    if(FUNCLIST[27].func!=0)
        (*FUNCLIST[27].func)();
}