#ifndef DISPLAY_H
#define DISPLAY_H

#include "ENCODE_SENSOR.h"
#include "DISPLAY.h"
#include "SERVO_MOTOR_CONTROL.h"

// void display(){
//     lcd_showstr(0,0,"L");
//     lcd_showint16(60,0,READ_DATA[0]);
//     lcd_showstr(0,1,"LM");
//     lcd_showint16(60,1,READ_DATA[1]);
//     lcd_showstr(0,2,"RM");
//     lcd_showint16(60,2,READ_DATA[2]);
//     lcd_showstr(0,3,"R");
//     lcd_showint16(60,3,READ_DATA[3]);
//     lcd_showstr(0,4,"div");
//     lcd_showint16(60,4,(READ_DATA[0]*100-READ_DATA[3]*100)/(READ_DATA[0]*100+READ_DATA[3]*100));
//     lcd_showstr(0,5,"SPPED");
//     lcd_showint16(60,5,(ENCODING_READ_RESULT()));
//     lcd_showstr(0,6,"ANGLE");
//     lcd_showint16(60,6,(SERVO_MOTOR_CONTROL()));
//     lcd_showstr(0,7,"duty");
    
// }