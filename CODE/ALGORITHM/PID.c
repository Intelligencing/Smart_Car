/*
 * @Description  : PID控制算法实现
 * @Author       : FZU Liao
 * @Date         : 2022-01-02 20:19:32
 * @LastEditors  : Liao
 * @LastEditTime : 2022-01-22 16:49:46
 * @FilePath     : \ALGORITHM\PID.c
 * Copyright 2022 FZU Liao, All Rights Reserved. 
 */

#include "PID.h"
#include "stdio.h"

void PID_SET_TARGET(PID* PID_CONTROL,float Param_Target){
    PID_CONTROL->TARGET_VALUE = Param_Target;
}

void PID_SET_FACTORS(PID* PID_CONTROL,float Param_P,float Param_I,float Param_D){
    PID_CONTROL->FACTOR_Proportional = Param_P;
    PID_CONTROL->FACTOR_Integral     = Param_I;
    PID_CONTROL->FACTOR_Differential = Param_D;
}

float PID_CALC_RESULT(PID* PID_CONTROL,float CURRENT_INPUT){
    float P , I , D;
    float PID_OUTPUT;
    float ERROR,d_ERROR;
    ERROR = PID_CONTROL->TARGET_VALUE - CURRENT_INPUT;
    PID_CONTROL->PID_SUM_ERROR += ERROR;
    if(PID_CONTROL->PID_X_MODE == PID_REALIZE_MODE){
        d_ERROR = PID_CONTROL->PID_LAST_ERROR - PID_CONTROL->PID_PREV_ERROR;
        P = PID_CONTROL->FACTOR_Proportional*ERROR;
        I = PID_CONTROL->FACTOR_Integral*PID_CONTROL->PID_SUM_ERROR;
        D = PID_CONTROL->FACTOR_Differential*d_ERROR;
    }else{
        d_ERROR = ERROR - 2*PID_CONTROL->PID_LAST_ERROR + PID_CONTROL->PID_PREV_ERROR;
        P = (ERROR-PID_CONTROL->PID_LAST_ERROR)*PID_CONTROL->FACTOR_Proportional;
        I = PID_CONTROL->FACTOR_Integral*ERROR;
        D = PID_CONTROL->FACTOR_Differential*d_ERROR;
    }
    PID_CONTROL->PID_PREV_ERROR = PID_CONTROL->PID_LAST_ERROR;
    PID_CONTROL->PID_LAST_ERROR = ERROR;
    PID_OUTPUT = P+I+D;
    return PID_OUTPUT;
}

void PID_INIT_NEWPID(PID* NEW_PID,float Param_P,float Param_I,float Param_D,float Param_Target,PID_CONTROL_MODE PID_MODE){
    //memset(NEW_PID,0,sizeof(struct PID_CONTROL_STRUCT));
    NEW_PID->PID_X_MODE = PID_MODE;
    NEW_PID->PID_PREV_ERROR     = 0;
    NEW_PID->PID_LAST_ERROR     = 0;
    NEW_PID->PID_SUM_ERROR      = 0;
    PID_SET_FACTORS(NEW_PID,Param_P,Param_I,Param_D);
    PID_SET_TARGET(NEW_PID,Param_Target);
}

void PID_DEINIT_PID(PID* PID_CONTROL){
    //free(PID_CONTROL);
}