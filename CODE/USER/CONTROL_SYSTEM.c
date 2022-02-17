#include "CONTROL_SYSTEM.h"
#include "SERVO_MOTOR_CONTROL.h"
#include "STEP_MOTOR_CONTROL.h"
#include "EM_SENSOR.h"
#include "ENCODE_SENSOR.h"
#include "LCD_show.h"
#include "headfile.h"

#define SPEED 400

CAR_STATUS CUR_STATUS;  //当前状态

int DATA[4];  //电磁传感器数据存储列表
int TARGET_SPEED;     //目标速度
int CURRENT_SPEED;    //当前速度
float ANGLE;          //舵机打角
int RES;

void (*func[7])();//函数指针数组，用于映射不同状态对应的函数

CAR_STATUS CAR_STATUS_JUDGE() {//状态判断
    float backup;//左右电感差值
    int TARGET_SPEED;
    int huan_dw;//环岛标志位

    if((DATA[0]-DATA[3])>0)  backup=DATA[0]-DATA[3];
    if((DATA[0]-DATA[3])<0)  backup=DATA[3]-DATA[1];
    TARGET_SPEED=430-(int)(backup*1.2);   //弯道最低+直道加速
    //分段PD
    if(backup<=50)     return STRAIGHT;
    /* * * 弯道处理 * * */
    if(50<backup<=200){
        SteeringPID_State(2);
        return ON_CURVE;
    }   
    if(200<backup){
         SteeringPID_State(3);
         return ON_CURVE;
    } 
     /* * * 环岛处理 * * */      
    if((DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
         DATA[1]<=70&&DATA[0]>=65&&DATA[0]<=70)   
         ||(DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
            DATA[1]<=70&&DATA[0]>=65&&DATA[0]<70)) {//环标志
        if(huan_dw==0) return INTO_CIRCLE;
        else {//防止再次入环
            huan_dw=0;
        }
    }
}

void SYS_INIT_ALL(){
    sys_clk=30000000;//时钟频率
    board_init();//固件初始化
    lcd_init();//显示屏初始化
    ISR_INIT();
    EnableGlobalIRQ();//中断初始化
}

void CONTROL_SYS_INIT(){
    //状态函数列表初始化
    func[0] = FUNC_STRAIGHT;
    func[1] = FUNC_INTO_CURVE;
    func[2] = FUNC_ON_CURVE;
    func[3] = FUNC_OUT_CURVE;
    func[4] = FUNC_INTO_CIRCLE;
    func[5] = FUNC_ON_CIRCLE;
    func[6] = FUNC_OUT_CIRCLE;
    
    EM_INIT();//电磁传感器初始化
    ENCODING_INIT();//编码器初始化
    StepMotorControl_INIT();//步进电机控制系统初始化
    SteeringControl_INIT();//舵机控制系统初始化
    lcd_clear(BLUE);
    lcd_clear(WHITE);//lcd刷新
}

void Data_update(){
    EM_READ(DATA);//读取数据
    LCD("L",DATA[0],0);//显示电感值
    LCD("LM",DATA[1],1);
    LCD("RM",DATA[2],2);
    LCD("R",DATA[3],3);
    LCD("SPEED",RES,4);//显示编码器读取数据
    RES = ENCODING_READ_RESULT();//编码器读取电机转速
}

void ControlSys() {
    //  ANGLE = SPEED(DATA, 0);
    //  StepMotorControl(RES,SPEED);
    //  SteeringControl(-ANGLE);
    CUR_STATUS = CAR_STATUS_JUDGE();
    //LCD("STATU",CUR_STATUS,8);
    (*func[CUR_STATUS])();
}

//前进函数
void FORWARD_FUNC(){
    ANGLE=ANGLE_GETANGLE(DATA,0);
    CURRENT_SPEED=ENCODING_READ_RESULT();//编码器计算当前速度
    TARGET_SPEED=SPEED; //min_SPEED + (max_SPEED - min_SPEED)/10*ANGLE;
    //利用舵机打角角度，处理出速度目标值
    StepMotorControl(RES,TARGET_SPEED);//电机输出
    SteeringControl(-ANGLE);
}

//直线行驶状态函数实现
void FUNC_STRAIGHT() {
    SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC();
}

//入弯状态函数实现
void FUNC_INTO_CURVE(){
    SteeringPID_State(ON_TURN);
    FORWARD_FUNC();
    CUR_STATUS = ON_CURVE;
}

//在弯道中状态函数实现
void FUNC_ON_CURVE(){
    FORWARD_FUNC();
}

//出弯状态函数实现
void FUNC_OUT_CURVE(){
    SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC();
    CUR_STATUS = STRAIGHT;
}

//入环状态函数实现
void FUNC_INTO_CIRCLE(){
    SteeringPID_State(ON_TURN);
    SteeringControl(10);
    delay_ms(1000);
    CUR_STATUS = ON_CIRCLE;
}

//在环岛中状态函数实现
void FUNC_ON_CIRCLE(){
    FORWARD_FUNC();
}

//出环状态函数实现
void FUNC_OUT_CIRCLE(){
    SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC();
    delay_ms(1000);
    CUR_STATUS = STRAIGHT;
}

