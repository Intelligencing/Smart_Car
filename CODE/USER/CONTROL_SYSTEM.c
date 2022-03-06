#include "CONTROL_SYSTEM.h"
#include "SERVO_MOTOR_CONTROL.h"
#include "STEP_MOTOR_CONTROL.h"
#include "EM_SENSOR.h"
#include "ENCODE_SENSOR.h"
#include "LCD_show.h"
#include "headfile.h"
#include "common.h"

#define SPEED 270

CAR_STATUS CUR_STATUS;  //当前状态

int DATA[4];  //电磁传感器数据存储列表
int TARGET_SPEED;     //目标速度
int CURRENT_SPEED;    //当前速度
float ANGLE;          //舵机打角
int RES;

void (*func[7])();//函数指针数组，用于映射不同状态对应的函数
int i,a;
a=0;
int SC_flag;//三叉路口标志位
int flag;

CAR_STATUS CAR_STATUS_JUDGE() {//状态判断
    float backup;//左右电感差值
    int huan_dw;//环岛标志位
			
	backup=(DATA[1]-DATA[2]>0 ? DATA[1]-DATA[2] : DATA[2]-DATA[1]);
    //分段PD
//	if (DATA[0]<80&&DATA[3]<80)
//    {
//			  SteeringPID_State(2);
//        return INTO_CURVE;/* code */
//    }
//    	//	 /*三叉处理*/
//	 if(DATA[1]<500&&DATA[2]<500&&DATA[0]<600&&DATA[3]<600&&SC_flag==0&&flag==0){//入三叉
//		 SteeringControl(-8); 
//		  delay_ms(150);
//		 SC_flag=1;
//	 }
//	 if(DATA[1]>1000||DATA[2]>1000&&SC_flag==1&&flag==0){//出三叉
//		 flag=1;//已经进入一次
//		 SteeringControl(-8);
//		  delay_ms(150);
//		 SC_flag=0;
//	 }
//	 if(DATA[1]<500&&DATA[2]<500&&DATA[0]<600&& DATA[3]<600&&SC_flag==0&&flag==1){//入三叉
//		 SteeringControl(8);
//		  delay_ms(150);
//		 SC_flag=1;
//	 }
//	 if(DATA[1]>1000||DATA[2]>1000&&SC_flag==1&&flag==1){//出三叉
//		 flag=0;
//		 SteeringControl(8);
//		 delay_ms(150);
//		 SC_flag=0;
//	 }
	 
    if(backup<=300&&a==0){
			return STRAIGHT;
		}
    /* * * 弯道处理 * * */
    if(300<backup&&backup<=600&&a==0){
        SteeringPID_State(1);
        return INTO_CURVE;
    }   
//   if(backup>250){
//        SteeringPID_State(2);
//        return ON_CURVE;
//   } 
	 if(backup>600||a<=1){
        a++;
		if(a>1) a=0;
        SteeringPID_State(2);
        return ON_CURVE;
   } 

	 
//	 /*十字路口处理*/
//	 if(DATA[0]>1000&&DATA[3]>1000&&DATA[1]>1000||DATA[2]>1000){
//		 SteeringControl(0);
//	 }
     /* * * 环岛处理 * * */ 
//		if(DATA[1]>2000&&DATA[2]>2000&&DATA[3]>DATA[0]) {//环标志
//			if(huan_dw==0) return INTO_CIRCLE;
//				 else {//防止再次入环
//							 huan_dw=0;
//				 }
//			if((DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
//					 DATA[1]<=70&&DATA[0]>=65&&DATA[0]<=70)   
//					 ||(DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
//							DATA[1]<=70&&DATA[0]>=65&&DATA[0]<70)) {//环标志
//					if(huan_dw==0) return INTO_CIRCLE;
//					else {//防止再次入环
//							huan_dw=0;
//					}
//			}
	//	}
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
	  SC_flag=0;//三叉路口标志位
    flag=0;
}

void Data_update(){
    EM_READ(DATA);//读取数据
    LCD("L",DATA[0],0);//显示电感值
    LCD("LM",DATA[1],1);
    LCD("RM",DATA[2],2);
    LCD("R",DATA[3],3);
	//LCD("FLAG",SC_flag,4);//显示编码器读取数据
    LCD("SPEED",RES,4);//显示编码器读取数据
    RES = ENCODING_READ_RESULT();//编码器读取电机转速
}

void ControlSys() {
    //  ANGLE = SPEED(DATA, 0);
    //  StepMotorControl(RES,SPEED);
    //  SteeringControl(-ANGLE);
    CUR_STATUS = CAR_STATUS_JUDGE();
    LCD("STATU",CUR_STATUS,8);
    (*func[CUR_STATUS])();

    
}

//前进函数
void FORWARD_FUNC(){
	  float backup;//左右电感差值
	  int TARGET_SPEED;
    ANGLE=ANGLE_GETANGLE(DATA,0);
    CURRENT_SPEED=ENCODING_READ_RESULT();//编码器计算当前速度
	  backup=(DATA[1]-DATA[2]>0 ? DATA[1]-DATA[2] : DATA[1]-DATA[2]);
    TARGET_SPEED=300-(int)(backup*0.1);   //弯道最低+直道加速0.013
    //TARGET_SPEED=SPEED; //min_SPEED + (max_SPEED - min_SPEED)/10*ANGLE;
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
	  delay_ms(1000);
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

