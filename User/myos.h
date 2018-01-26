#ifndef __MYOS_H
#define __MYOS_H
#include "stdint.h"
#define LINE_NUM_GET(num)   num = __LINE__; case __LINE__:
#define PROCESS_BEGIN(s)    switch(s) { case 0:
#define PROCESS_END()       }

typedef struct _TaskStruct
{
    void (*TaskHook)(void);     // 要运行的任务函数
    uint64_t Counter;           // 任务全局节拍
    uint32_t LineNum;           // 行号
    uint8_t Run;                // 程序运行标记：0-不运行，1运行
} TaskStruct;


#define PROCESS_DELAY(task, n)      do                                              \
                                    {                                               \
                                        task.Counter = GlobalTimerCnt;              \
                                        LINE_NUM_GET(task.LineNum);                 \
                                        if( (GlobalTimerCnt - task.Counter) > n )   \
                                        {                                           \
                                            break;                                  \
                                        }                                           \
                                        return;                                     \
                                    } while(0)

									
									
									
									
#endif




									