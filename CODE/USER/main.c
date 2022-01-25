#include "CONTROL_SYSTEM.h"
#include "headfile.h"
#include "LCD_show.h"
#define TARGET_SPEED 200

void SYS_INIT_ALL(){
    sys_clk=30000000;
    board_init();
    lcd_init();
    ISR_INIT();
    EnableGlobalIRQ();
    
}

//begin-----------------------------------------------------------------
// ENCODE_SENSOR SENSOR;
int res;
int datalist[4];      //电磁传感器数据存储列表

void display(){
    // debug-----------------------------------------------------------------
    LCD_display("L",datalist[0],0);
    LCD_display("LM",datalist[1],1);
    LCD_display("RM",datalist[2],2);
    LCD_display("R",datalist[3],3);
    //LCD_display("dir",EM_CALC_POS_RES(datalist)*1000,4);
//-----------------------------------------------------------------
}
//end-----------------------------------------------------------------

void main(){
    SYS_INIT_ALL();
    lcd_clear(BLUE);
    lcd_clear(WHITE);
    MYSYS_INIT();
//begin-----------------------------------------------------------------
    pit_timer_ms(TIM_1,1);
//end-----------------------------------------------------------------
    while(1){
        Data_update();
        MyControlSys_TASK();
        // // res = ENCODING_READ_RESULT();
        // // STEP_MOTOR_CONTROL(RES,TARGET_SPEED);
        // // delay_ms(5);
        // EM_READ_SENSOR(datalist);
        // LCD_display("ANGLE",SERVO_MOTOR_CONTROL(datalist,0),5);
        // display();
    }
}