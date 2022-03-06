#ifndef CONTROL_SYSTEM_H
#define CONTROL_SYSTEM_H

typedef enum { //车状态枚举
    STRAIGHT, 
    INTO_CURVE,
    ON_CURVE,
    OUT_CURVE,
    INTO_CIRCLE,
    ON_CROSS,
    OUT_CIRCLE,
    ON_JUNCTION
} CAR_STATUS;

//CAR_STATUS CAR_STATUS_JUDGE();
void SYS_INIT_ALL();
void CONTROL_SYS_INIT();
void Data_update();
void ControlSys();
void FORWARD_FUNC(float userangle,int SPEED);//前进函数
void FUNC_STRAIGHT(); //直线行驶状态函数实现
void FUNC_INTO_CURVE();//入弯状态函数实现
void FUNC_ON_CURVE();//在弯道中状态函数实现
void FUNC_OUT_CURVE();//出弯状态函数实现
void FUNC_INTO_CIRCLE();//入环状态函数实现
void FUNC_CROSS();//在十字路口状态函数实现
void FUNC_OUT_CIRCLE();//出环状态函数实现
void FUNC_JUNCTION();//三叉路口状态函数实现



#endif