#include "EM_Calc.h"

#define L  1
#define LM 0
#define RM 3
#define R  2

#define ParamA 2.5
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