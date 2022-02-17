#include "LCD_show.h"

void LCD(const int8* str,int16 value,int8 row_num){
    lcd_showstr(0,row_num,str);
    lcd_showint16(40,row_num,value);
}