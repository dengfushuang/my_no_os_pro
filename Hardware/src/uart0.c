
#include  "uart0.h"

extern uint32 SystemCoreClock;
uint8  UART0Init(uint8_t BPS)
{
    uint16 Fdiv;
    uint32 bps; 
    //使能以UART0控制器电源    
    LPC_SC->PCONP |= (1<<3);
    // Enable UART0 Pins.
    LPC_IOCON->P0_2 = 0x01;     //UART0_TXD
    LPC_IOCON->P0_3 = 0x01;     //UART0_RXD
	
    switch ( BPS )
    {
        case 1 :
             bps = 2400;
            break;
        case 2 :
             bps = 4800;
            break;
        case 3 :
             bps = 9600;
            break;
        case 4 :
             bps = 14400;
            break;
        case 5 :
             bps = 19200;
            break;
        case 6 :
             bps = 38400;
            break;
        case 7 :
             bps = 56000;
            break;
        case 8 :
             bps = 57600;
            break;
         case 9 :
             bps = 115200;
            break;               
        default:  break;
    }
    LPC_UART0->LCR = 0x80;                      // 允许访问分频因子寄存器     
    Fdiv = (PeripheralClock / 16) / bps;        // 设置波特率 
    LPC_UART0->DLM = Fdiv / 256;
	  LPC_UART0->DLL = Fdiv % 256;
    LPC_UART0->LCR = 0x03;                      // 禁止访问分频因子寄存器 
                                                // 且设置为8,1,n 
	  LPC_UART0->IER = 0x05;                      // 允许接收和发送中断 
    LPC_UART0->FCR = 0x87;                      // 初始化FIFO 

    NVIC_EnableIRQ(UART0_IRQn);                 // Enable UART0 interrupt 
	return 0;
}

void UART0Putch(uint8 Data)
{
    while ((LPC_UART0->LSR & 0x00000020) == 0);                                            /* UART0发送保持寄存器空 */
    LPC_UART0->THR = Data;
    LPC_UART0->IER = LPC_UART0->IER | 0x02;     /* 允许发送中断 */
}

 void UART0Put_str(uint8 *Data, uint16 NByte)
{
    while (NByte-- > 0)
    {
        UART0Putch(*Data++);
    }
}

void UART0Write_Str(uint8 *Data)
{
    while (*Data != '\0' )
    {
        UART0Putch(*Data++);
    }
}

uint8 UART0Getch(void)
{
    uint8 err;
    while ((LPC_UART0->LSR & 0x00000001) == 0)
    {                                           /* 没有收到数据 */
        LPC_UART0->IER = LPC_UART0->IER | 0x01; /* 允许接收中断 */
    }
    err = LPC_UART0->RBR;                       /* 读取收到的数据 */
    return err;
}

void UART0_IRQHandler (void) 
{
    uint8 IIR, temp;

    while(((IIR = LPC_UART0->IIR) & 0x01) == 0)
    {                                                   /* 有中断未处理完 */
        switch (IIR & 0x0e)
        {
            case 0x02: LPC_UART0->IER = LPC_UART0->IER & (~0x02);        /* 队列空，则禁止发送中断 */
                break;
            case 0x04:                                  /* 接收数据可用 */
                LPC_UART0->IER = LPC_UART0->IER & (~0x01);                /* 禁止接收及字符超时中断 */
                break;
            case 0x06:                                  /* 接收线状态   */
                temp = LPC_UART0->LSR;
                break;
            case 0x0c:                                  /* 字符超时指示 */
                LPC_UART0->IER = LPC_UART0->IER & (~0x01);                /* 禁止接收及字符超时中断 */
                break;
            default :
            	temp = LPC_UART0->LSR;
                break;
        }
    }
}

/*********************************************************************************************************
**                            End Of File
********************************************************************************************************/
