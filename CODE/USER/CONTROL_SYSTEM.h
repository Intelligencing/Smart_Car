#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

typedef enum { //车状态枚举
    STRAIGHT, 
    INTO_CURVE,
    ON_CURVE,
    OUT_CURVE,
    INTO_CIRCLE,
    ON_CIRCLE,
    OUT_CIRCLE
} MyCAR_STATUS;

void MYSYS_INIT();
void Data_update();
void FORWARD_FUNC();//前进函数
void FUNC_STRAIGHT(); //直线行驶状态函数实现
void FUNC_INTO_CURVE();//入弯状态函数实现
void FUNC_ON_CURVE();//在弯道中状态函数实现
void FUNC_OUT_CURVE();//出弯状态函数实现
void FUNC_INTO_CIRCLE();//入环状态函数实现
void FUNC_ON_CIRCLE();//在环岛中状态函数实现
void FUNC_OUT_CIRCLE();//出环状态函数实现
void My_routineTask();
//MyCAR_STATUS CAR_STATUS_JUDGE();

#endif