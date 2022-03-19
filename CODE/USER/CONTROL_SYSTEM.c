#include "CONTROL_SYSTEM.h"
#include "SERVO_MOTOR_CONTROL.h"
#include "STEP_MOTOR_CONTROL.h"
#include "EM_SENSOR.h"
#include "ENCODE_SENSOR.h"
#include "LCD_show.h"
#include "headfile.h"
#include "common.h"
#include "EM_Calc.h"

CAR_STATUS CUR_STATUS;  //当前状态

int DATA[4];  //电磁传感器数据存储列表
int RES;
float backup;//左右电感差值
void (*func[8])();//函数指针数组，用于映射不同状态对应的函数
int SC_flag;//三叉路口标志位
int flag;
int TARGET_SPEED;
float ANGLE;
int b,h,s,SPO;
CAR_STATUS CAR_STATUS_JUDGE() {//状态判断
//    int huan_dw;//环岛标志位
//	if(huan_dw==0&&DATA[0]>1400&&(DATA[3]>1400||DATA[1]>2000)&&DATA[0]>DATA[3]) {//右环入
//		SteeringControl(40);
//		h++;
//	}
//	if(huan_dw==1&&DATA[0]>1400&&(DATA[3]>1400||DATA[1]>2000)&&DATA[0]>DATA[3])//右环出
//		SteeringControl(0);
//	
//	

//	      /******三叉判断********/
//	if(flag==0&&DATA[2]+DATA[1]<1700&&DATA[0]>450&&DATA[3]>450&&DATA[0]<1400&&DATA[3]<1400){//三叉右打角
//	 SteeringControl(-40);
//	 s++ ;
//	}//s==12
//	if(flag==1&&DATA[2]+DATA[1]<1700&&DATA[0]>450&&DATA[3]>450&&DATA[0]<1400&&DATA[3]<1400)//三叉左打脚
//		SteeringControl(40);

//	       /*****出环、出三叉判断********/
//		if(s>1&&DATA[0]>1400)flag=1;
  /*三叉处理*/
//	if(DATA[1]<500&&DATA[2]<500&&DATA[0]<600&&DATA[3]<600&&SC_flag==0&&flag==0){//入左三叉
//		    SC_flag=1;
//        SteeringControl(-40);
//        return ON_JUNCTION;
//	}
//	if(DATA[1]>1000||DATA[2]>1000&&SC_flag==1&&flag==0){//出左三叉
//		flag=1;//已经进入一次 
//        SteeringControl(-40); 
//		SC_flag=0;
//        return ON_JUNCTION;
//	} 
//    if(DATA[1]<500&&DATA[2]<500&&DATA[0]<600&&DATA[3]<600&&SC_flag==0&&flag==1){//入右三叉
//		SC_flag=1;
//        SteeringControl(40);
//        return ON_JUNCTION;
//	}
//	if(DATA[1]>1000||DATA[2]>1000&&SC_flag==1&&flag==1){//出右三叉
//		flag=0;//入三叉标志位清零
//        SteeringControl(40);
//		SC_flag=0;
//        return ON_JUNCTION;
//	} 
//	 /*十字路口处理*/
//	if(DATA[0]>1000&&DATA[3]>1000&&DATA[1]>1000||DATA[2]>1000){
//		return ON_CROSS;
//	}
//     /* * * 环岛处理 * * */ 
//	if(DATA[1]>2000&&DATA[2]>2000&&DATA[3]>DATA[0]&&huan_dw==0) {//环标志
//		huan_dw++;
//        return INTO_CIRCLE;
//   }
//   if(DATA[1]>2000&&DATA[2]>2000&&DATA[3]>DATA[0]&&huan_dw==1) {//环标志
//		huan_dw++;
//        return OUT_CIRCLE;
//   }
//   else{//防止再次入环
      //  return STRAIGHT;
//   }
	 
//		if((DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
//			DATA[1]<=70&&DATA[0]>=65&&DATA[0]<=70)   
//			||(DATA[0]>90&&DATA[1]>90&&DATA[1]>=65&&
//			DATA[1]<=70&&DATA[0]>=65&&DATA[0]<70)) {//环标志
//			if(huan_dw==0) return INTO_CIRCLE;
//			else {//防止再次入环
//					huan_dw=0;
//				}
//		}

    //分段PD
//	if (DATA[0]<80&&DATA[3]<80)
//    {
//		SteeringPID_State(2);
//      return INTO_CURVE;/* code */
//    }
// if(backup<=300&&a==0){
// 		return STRAIGHT;
// 	}
// /* * * 弯道处理 * * */
// if(300<backup&&backup<=600&&a==0){
//     SteeringPID_State(1);
//     return INTO_CURVE;
// }   
//   if(backup>250){
//        SteeringPID_State(2);
//        return ON_CURVE;
//   } 
// 	 if(backup>600||a<=1){
//         a++;
// 		if(a>1) a=0;
//         SteeringPID_State(2);
//         return ON_CURVE;
//    } 
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
    func[5] = FUNC_CROSS;
    func[6] = FUNC_OUT_CIRCLE;
    func[7] = FUNC_JUNCTION;
    EM_INIT();//电磁传感器初始化
    ENCODING_INIT();//编码器初始化
    StepMotorControl_INIT();//步进电机控制系统初始化
    SteeringControl_INIT();//舵机控制系统初始化
    lcd_clear(BLUE);
    lcd_clear(WHITE);//lcd刷新
	  SC_flag=0;//三叉路口标志位
    flag=0;
	  SPO=0;
	  b=0;
}

void Data_update(){
    int ERROR;
    EM_READ(DATA);//读取数据
    ERROR = EM_CALC_POS_RES(DATA)*1000;
    LCD("R",DATA[0],0);//显示电感值
    LCD("RM",DATA[1],1);
    LCD("LM",DATA[2],2);
    LCD("L",DATA[3],3);
    //LCD("SPEED",RES,4);//显示编码器读取数据
    //LCD("ANGLE",ANGLE,5);//显示角度
    LCD("D",ERROR,4);//显示误差
    RES = ENCODING_READ_RESULT();//编码器读取电机转速
    backup=(DATA[1]-DATA[2]>0 ? DATA[1]-DATA[2] : DATA[2]-DATA[1]);
}

void ControlSys() {
   //CUR_STATUS = CAR_STATUS_JUDGE();
  // LCD("STATU",CUR_STATUS,8);
   //(*func[CUR_STATUS])();
	FORWARD_FUNC(0,0);
    
}

//前进函数
void FORWARD_FUNC(float USERANGLE,int SPEED){	  
    float Kp;  
    Kp = (backup/((DATA[1]+DATA[2]+DATA[0]+DATA[3])*0.53))*130;//60
    //LCD("Kp",Kp,5);//显示角度
    ANGLE = ANGLE_GETANGLE(DATA,USERANGLE,Kp,0,70);//位置式PIDKp = (backup/(DATA[1]+DATA[2]))*50;
		if(DATA[0]<10&&DATA[3]>300) ANGLE=40;
		if(DATA[3]<10&&DATA[0]>300) ANGLE=-40;
	 //60ANGLE = ANGLE_GETANGLE(DATA,USERANGLE,Kp,34,25);//位置式PID
	  LCD("ANGLE",ANGLE,8);//显示角度 
    if (SPEED == 0) TARGET_SPEED = (400-(int)(backup*0.16));
    else  TARGET_SPEED=SPEED;  //弯道最低+直道加速0.013
	  b=(b>RES ? b : RES);
    LCD("TS",RES,5);
	  if(RES > 2000)  TARGET_SPEED=0;//下坡限速 
		if(DATA[1]<10) TARGET_SPEED=-1000; 
		//if(DATA[1]+DATA[2]>1800&&DATA[1]+DATA[2]<2000&&DATA[1]<1100&&DATA[2]<1100&&DATA[0]+DATA[3]>500)  SPO=1;
    //LCD("SP",SPO,8);	
	//TARGET_SPEED=SPEED; //min_SPEED + (max_SPEED - min_SPEED)/10*ANGLE;
    //利用舵机打角角度，处理出速度目标值
    StepMotorControl(RES,TARGET_SPEED);//电机输出
    SteeringControl(-ANGLE);
}

//直线行驶状态函数实现
void FUNC_STRAIGHT() {
    //SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC(0,0);
}

//入弯状态函数实现
void FUNC_INTO_CURVE(){
    //SteeringPID_State(ON_TURN);
    FORWARD_FUNC(0,0);
    CUR_STATUS = ON_CURVE;
}

//在弯道中状态函数实现
void FUNC_ON_CURVE(){
    FORWARD_FUNC(0,0);
}

//出弯状态函数实现
void FUNC_OUT_CURVE(){
    //SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC(0,0);
    CUR_STATUS = STRAIGHT;
}

//入环状态函数实现
void FUNC_INTO_CIRCLE(){
    //SteeringPID_State(ON_TURN);
	delay_ms(1000);
    if(DATA[0]>DATA[3]) SteeringControl(40);
    else SteeringControl(-40);
    delay_ms(1000);
    CUR_STATUS = INTO_CIRCLE;
}

//在十字路口中状态函数实现
void FUNC_CROSS(){
    FORWARD_FUNC(1,0);
}

//出环状态函数实现
void FUNC_OUT_CIRCLE(){
    //SteeringPID_State(ON_STRAIGHT);
    FORWARD_FUNC(0,0);
    delay_ms(1000);
    if(DATA[0]>DATA[3]) SteeringControl(-40);
    else SteeringControl(40);
    delay_ms(1000);
    CUR_STATUS = STRAIGHT;
}
void FUNC_JUNCTION(){
    FORWARD_FUNC(0,0);
}

