#include "CONTROL_SYSTEM.h"
#include "headfile.h"
#include "LCD_show.h"

void main(){
    SYS_INIT_ALL();//底层初始化
    CONTROL_SYS_INIT();//控制程序初始化
    pit_timer_ms(TIM_1,2);//任务时钟设置
    while(1){
        Data_update();//数据更新
        ControlSys();//执行任务
    }
}