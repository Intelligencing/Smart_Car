#include "CONTROL_SYSTEM.h"
#include "SERVO_MOTOR_CONTROL.h"
#include "STEP_MOTOR_CONTROL.h"
#include "EM_SENSOR.h"
#include "EM_FILTER.h"
#include "ENCODE_SENSOR.h"
#include "LCD_show.h"
#include "headfile.h"

#define SPEED 1000
#define AUTO_CONTROL 0

// MyCAR_STATUS TEMP_STATUS; //临时状态变量
MyCAR_STATUS CUR_STATUS;  //当前状态
int EM_DATA_LIST[4];  //电磁传感器数据存储列表
int TARGET_SPEED;     //目标速度
int CURRENT_SPEED;    //当前速度
int index;            //临时变量
float ANGLE;          //舵机打角
int RES_L;

EM_FILTER FILTER;        //电磁传感器               
//ENCODE_SENSOR ENCODE_L;  //左轮编码器

//void (*func_list[7])();//函数指针数组，用于映射不同状态对应的函数

MyCAR_STATUS CAR_STATUS_JUDGE() {//状态判断

    return STRAIGHT;
}

void MYSYS_INIT(){
    //状态函数列表初始化
    // func_list[0] = FUNC_STRAIGHT;
    // func_list[1] = FUNC_INTO_CURVE;
    // func_list[2] = FUNC_ON_CURVE;
    // func_list[3] = FUNC_OUT_CURVE;
    // func_list[4] = FUNC_INTO_CIRCLE;
    // func_list[5] = FUNC_ON_CIRCLE;
    // func_list[6] = FUNC_OUT_CIRCLE;

    //FLAG=OFF;
    
    EM_INIT_SENSOR();//电磁传感器初始化
    ENCODING_INIT();//编码器初始化
    MyStepMotorControl_INIT();      //初始化步进电机控制系统
    MySteeringControl_INIT();       //初始化舵机
}

void Data_update(){
    // debug-----------------------------------------------------------------
    LCD_display("L",EM_DATA_LIST[0],0);
    LCD_display("LM",EM_DATA_LIST[1],1);
    LCD_display("RM",EM_DATA_LIST[2],2);
    LCD_display("R",EM_DATA_LIST[3],3);
    LCD_display("LV",RES_L,4);
//-----------------------------------------------------------------
    EM_READ_SENSOR(EM_DATA_LIST);                 //读取数据
    RES_L = ENCODING_READ_RESULT();//编码器读取电机转速
}

void MyControlSys_TASK() {
    ANGLE = MySteeringControl_GETANGLE(EM_DATA_LIST, 0);
    MyStepMotorControl_TASK(RES_L,SPEED);
    MySteeringControl_TASK(ANGLE);
    // CUR_STATUS = CAR_STATUS_JUDGE();
    // (*func_list[CUR_STATUS])();
}

//前进函数
void FORWARD_FUNC(){
    ANGLE=MySteeringControl_GETANGLE(EM_DATA_LIST,0);
    CURRENT_SPEED=ENCODING_READ_RESULT();//编码器计算当前速度
    TARGET_SPEED=SPEED; //min_SPEED + (max_SPEED - min_SPEED)/10*ANGLE;
    //利用舵机打角角度，处理出速度目标值
    MyStepMotorControl_TASK(RES_L,TARGET_SPEED);//电机输出
}

//直线行驶状态函数实现
void FUNC_STRAIGHT() {
    FORWARD_FUNC();
}

//入弯状态函数实现
void FUNC_INTO_CURVE(){
    MySteeringPIDAdapter_State(ON_TURN);
    FORWARD_FUNC();
    CUR_STATUS = ON_CURVE;
}

//在弯道中状态函数实现
void FUNC_ON_CURVE(){
    FORWARD_FUNC();
}

//出弯状态函数实现
void FUNC_OUT_CURVE(){
    MySteeringPIDAdapter_State(ON_STRAIGHT);
    FORWARD_FUNC();
    CUR_STATUS = STRAIGHT;
}

//入环状态函数实现
void FUNC_INTO_CIRCLE(){
    MySteeringPIDAdapter_State(ON_TURN);
    MySteeringControl_TASK(10);
    delay_ms(1000);
    CUR_STATUS = ON_CIRCLE;
}

//在环岛中状态函数实现
void FUNC_ON_CIRCLE(){
    FORWARD_FUNC();
}

//出环状态函数实现
void FUNC_OUT_CIRCLE(){
    MySteeringPIDAdapter_State(ON_STRAIGHT);
    FORWARD_FUNC();
    delay_ms(1000);
    CUR_STATUS = STRAIGHT;
}

