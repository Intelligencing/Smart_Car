#ifndef __PID_H__
#define __PID_H__

typedef enum{
    PID_REALIZE_MODE,
    PID_INCREASE_MODE
}PID_CONTROL_MODE;

struct PID_CONTROL_STRUCT{
    
    PID_CONTROL_MODE PID_X_MODE;    //PID工作模式

    float FACTOR_Proportional;      //比例系数
    float FACTOR_Integral;          //积分系数
    float FACTOR_Differential;      //微分系数
    
    float TARGET_VALUE;             //目标值
    
    float PID_LAST_ERROR;           //前一次误差记录
    float PID_PREV_ERROR;           //前两次误差记录
    float PID_SUM_ERROR;            //误差积分
    
};

typedef struct PID_CONTROL_STRUCT PID;

void PID_INIT_NEWPID(PID* NEW_PID,float Param_P,float Param_I,float Param_D,float Param_Target,PID_CONTROL_MODE PID_MODE);

void PID_SET_TARGET(PID* PID_CONTROL,float Param_Target);

void PID_SET_FACTORS(PID* PID_CONTROL,float Param_P,float Param_I,float Param_D);

float PID_CALC_RESULT(PID* PID_CONTROL,float CURRENT_INPUT);


#endif