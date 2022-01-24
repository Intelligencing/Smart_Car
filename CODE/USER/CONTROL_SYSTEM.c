#include "CONTROL_SYSTEM.h"

#define min_SPEED 1             
#define max_SPEED 2             
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

void (*func_list[7])();//函数指针数组，用于映射不同状态对应的函数

MyCAR_STATUS CAR_STATUS_JUDGE() {//状态判断

    return STRAIGHT;
}

void MYSYS_INIT(){
    //状态函数列表初始化
    func_list[0] = FUNC_STRAIGHT;
    func_list[1] = FUNC_INTO_CURVE;
    func_list[2] = FUNC_ON_CURVE;
    func_list[3] = FUNC_OUT_CURVE;
    func_list[4] = FUNC_INTO_CIRCLE;
    func_list[5] = FUNC_ON_CIRCLE;
    func_list[6] = FUNC_OUT_CIRCLE;

    //FLAG=OFF;
    
    EM_SENSOR_INIT();//电磁传感器初始化
    ENCODING_INIT();//编码器初始化
    SERVO_MOTOR_PID_INIT();//初始化舵机PID
    SERVO_MOTOR_INIT();//初始化舵机控制系统
    STEP_MOTOR_INIT();//初始化步进电机控制系统
    STEP_MOTOR_PID_INIT();//初始化步进电机PID
    EM_FILTER_INIT(&FILTER);//滤波器初始化
}

void Data_update(){
    // for (index = 0; index < 6; index++) {
    EM_READ_SENSOR(EM_DATA_LIST);                 //读取数据
    //     EM_FILTER_ADD_SAMPLE(&FILTER, EM_DATA_LIST);  //加入滤波器中
    // }
    //EM_FILTER_READ_RESULT(&FILTER, EM_DATA_LIST);  //获取滤波结果
    RES_L = ENCODING_READ_RESULT();//编码器读取电机转速
}

//前进函数
void FORWARD_FUNC(){
    ANGLE=SERVO_MOTOR_CONTROL(EM_DATA_LIST);
    CURRENT_SPEED=ENCODING_READ_RESULT();//编码器计算当前速度
    TARGET_SPEED=SPEED; //min_SPEED + (max_SPEED - min_SPEED)/10*ANGLE;
    //利用舵机打角角度，处理出速度目标值
    STEP_MOTOR_CONTROL(RES_L,TARGET_SPEED);//电机输出
}

//直线行驶状态函数实现
void FUNC_STRAIGHT() {
    FORWARD_FUNC();
}

//入弯状态函数实现
void FUNC_INTO_CURVE(){
    MySTEERING_PID_STATE(ON_TURN);
    FORWARD_FUNC();
    CUR_STATUS = ON_CURVE;
}

//在弯道中状态函数实现
void FUNC_ON_CURVE(){
    FORWARD_FUNC();
}

//出弯状态函数实现
void FUNC_OUT_CURVE(){
    MySTEERING_PID_STATE(ON_STRAIGHT);
    FORWARD_FUNC();
    CUR_STATUS = STRAIGHT;
}

//入环状态函数实现
void FUNC_INTO_CIRCLE(){
    MySTEERING_PID_STATE(ON_TURN);
    SERVO_MOTOR_ANGLE(10);
    delay_ms(1000);
    CUR_STATUS = ON_CIRCLE;
}

//在环岛中状态函数实现
void FUNC_ON_CIRCLE(){
    FORWARD_FUNC();
}

//出环状态函数实现
void FUNC_OUT_CIRCLE(){
    MySTEERING_PID_STATE(ON_STRAIGHT);
    FORWARD_FUNC();
    delay_ms(1000);
    CUR_STATUS = STRAIGHT;
}

void My_routineTask() {
    ANGLE = SERVO_MOTOR_CONTROL(EM_DATA_LIST, 0);
   STEP_MOTOR_CONTROL(RES_L,SPEED);
    SERVO_MOTOR_ANGLE(ANGLE_ADAPTER(ANGLE));
    // CUR_STATUS = CAR_STATUS_JUDGE();
    // (*func_list[CUR_STATUS])();
}