#include "user_config.h"
#include "myos.h"
unsigned int GlobalTimerCnt = 0;
void test_task1(void);
void test_task2(void);
void test_task3(void);
TaskStruct Task[3];

int main()
{
	uint8_t i;
	uint32_t t;
	Task[0].TaskHook = test_task1;
	Task[1].TaskHook = test_task2;
	Task[2].TaskHook = test_task3;
	SystemInit();
	RUN_LED_INIT;
	SYSTICK_InternalInit(1);
	SYSTICK_IntCmd(ENABLE);
	SYSTICK_Cmd(ENABLE);
	UART0Init(9);
	while(1)
	{

		for(i = 0 ;i < 3;i++)
		{
			Task[i].TaskHook();
		}
	}
	return 0;
}
void SysTick_Handler(void)
{
	GlobalTimerCnt++;
}
void test_task1(void)	
{
	PROCESS_BEGIN(Task[0].LineNum);
	while(1)
	{
		PROCESS_DELAY(Task[0],1000);
		RUN_LED_ON;
		PROCESS_DELAY(Task[0],1000);
		RUN_LED_OFF;
	}
	PROCESS_END();
}
void test_task2(void)	
{
	PROCESS_BEGIN(Task[1].LineNum);
	while(1)
	{
		UART0Write_Str((uint8_t *)"this is MSG1\r\n");
		PROCESS_DELAY(Task[1],1000);
		UART0Write_Str((uint8_t *)"this is aabbcc\r\n");
		PROCESS_DELAY(Task[1],1000);
		RUN_LED_OFF;
	}
	PROCESS_END(); 
}
void test_task3(void)	
{
	PROCESS_BEGIN(Task[2].LineNum);
	while(1)
	{
		UART0Write_Str((uint8_t *)"this is me\r\n");
		PROCESS_DELAY(Task[2],1500);
		UART0Write_Str((uint8_t *)"this is he\r\n");
		PROCESS_DELAY(Task[2],500);
		RUN_LED_OFF;
	}
	PROCESS_END();
}