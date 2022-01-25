/*
 * @Description  : 差和比差加权算法实现
 * @Author       : FZU Liao
 * @Date         : 2022-01-10 12:39:00
 * @LastEditors  : Liao
 * @LastEditTime : 2022-01-23 20:52:58
 * @FilePath     : \ALGORITHM\EM_Calc.c
 * Copyright 2022 FZU Liao, All Rights Reserved. 
 */

#include "EM_Calc.h"

#define L  1
#define LM 0
#define RM 3
#define R  2

#define ParamA 1
#define ParamB 1

float EM_CALC_POS_RES(int* EM_data){
   float RES;
   int i;
   for(i=0;i<4;i++){
       if(EM_data[i]<10) EM_data[i]=0; 
   }
   RES = (EM_data[LM]-EM_data[RM])>0 ? (
       ((float)(EM_data[L]-EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
       /((float)(EM_data[L]+EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
    ):(
        ((float)(EM_data[L]-EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
        /((float)(EM_data[L]+EM_data[R])*ParamA + (float)(EM_data[RM]-EM_data[LM])*ParamB)
    );
   return RES;
}