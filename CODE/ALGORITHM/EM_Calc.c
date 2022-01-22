#include "EM_Calc.h"

#define L 0
#define LM 1
#define RM 2
#define R 3

#define ParamA 1
#define ParamB 2


float EM_CALC_POS_RES(int *EM_data){
    float RES;
    RES = (EM_data[LM]-EM_data[RM])>0 ? (
       ((float)(EM_data[L]-EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
       /((float)(EM_data[L]+EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
    ):(
        ((float)(EM_data[L]-EM_data[R])*ParamA + (float)(EM_data[LM]-EM_data[RM])*ParamB)
        /((float)(EM_data[L]+EM_data[R])*ParamA + (float)(EM_data[RM]-EM_data[LM])*ParamB)
    );
   return RES;
}