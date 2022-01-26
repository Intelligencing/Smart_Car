
#ifndef __EM_FILTER_H__
#define __EM_FILTER_C__

#define LIST_LENGTH 4

struct FILTER_STRUCT{
    int MAX_RANGE;
    int MIN_RANGE;
    int times;
    int FILTER_LIST[LIST_LENGTH];
    int MAX_LIST[LIST_LENGTH];
    int MIN_LIST[LIST_LENGTH];
};

typedef struct FILTER_STRUCT EM_FILTER;

/**
 * @description: 初始化滤波器
 * @param FILTER EM_FILTER* 滤波器指针
 * @param max int 滤波器限幅 上限
 * @param min int 滤波器限幅 下限
 * @return *
 * @example: 
 */
void EM_FILTER_INIT(EM_FILTER*);

/**
 * @description: 滤波器添加一次样本
 * @param FILTER EM_FILTER* 滤波器指针
 * @param DATA_SAMPLE_LIST int* 样本数组
 * @return *
 * @example: 
 */
void EM_FILTER_ADD_SAMPLE(EM_FILTER* FILTER,int* DATA_SAMPLE_LIST);

/**
 * @description: 计算滤波结果并填入RES_SET数组中
 * @param FILTER EM_FILTER* 滤波器指针
 * @param RES_SET int* 结果数组
 * @return *
 * @example: 
 */
void EM_FILTER_READ_RESULT(EM_FILTER* FILTER,int* RES_SET);
#endif