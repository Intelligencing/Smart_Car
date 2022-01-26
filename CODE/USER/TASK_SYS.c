#include "headfile.h"
#include "TASK_SYS.h"

TASK* TaskList[TASK_MAX_N];

void Task_Excute(TASK* task){
    if(task == 0) return;
    task->COUNTER++;
    task->COUNTER%=task->THRESHOLD;
    if(task->COUNTER==0) (*task->FUNC)();
}

void TASK_STATE_UPDATE(){
    int i;
    for(i=0;i<TASK_MAX_N;i++){
        Task_Excute(TaskList[i]);
    }
}

void TASK_INIT_TASKSYS(){
    lcd_clear(RED);
    lcd_clear(BLUE);
    SET_ISR_FUNC(TM1_interrupt,TASK_STATE_UPDATE);
    pit_timer_ms(TIM_1,1);
}

void TASK_INIT_NEWTASK(TASK* task,uint16 Threshold,void (*func)()){
    //memset(task,0,sizeof(task));
    task->COUNTER = 0;
    task->THRESHOLD = Threshold;
    task->FUNC = func;
}

void TASK_SETID(uint8 ID,TASK* task){
    task->ID=ID;
}

void TASK_SETFUNC(void (*func)(),TASK* task){
    task->FUNC=func;
}

void TASK_ADD_TASK(TASK* task){
    int i;
    for (i = 0; i < TASK_MAX_N; i++) {
        if(TaskList[i]==0){
            TaskList[i]=task;
            TASK_SETID(i,task);
            return ;
        }
    }
}

void TASK_DELETE_TASK(TASK* task){
    TaskList[task->ID]=0;
}

void TASK_PAUSE_TASKSYS(){

}

void TASK_DEINIT_TASKSYS(){
    int i;
    for (i = 0; i < TASK_MAX_N; i++) {
        TaskList[i] = 0;
    }
}

