#ifndef __MYOS_H
#define __MYOS_H
#include "stdint.h"
#define LINE_NUM_GET(num)   num = __LINE__; case __LINE__:
#define PROCESS_BEGIN(s)    switch(s) { case 0:
#define PROCESS_END()       }

typedef struct _TaskStruct
{
    void (*TaskHook)(void);     // Ҫ���е�������
    uint64_t Counter;           // ����ȫ�ֽ���
    uint32_t LineNum;           // �к�
    uint8_t Run;                // �������б�ǣ�0-�����У�1����
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




									