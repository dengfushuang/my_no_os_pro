
#include  "uart0.h"

extern uint32 SystemCoreClock;
uint8  UART0Init(uint8_t BPS)
{
    uint16 Fdiv;
    uint32 bps; 
    //ʹ����UART0��������Դ    
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
    LPC_UART0->LCR = 0x80;                      // ������ʷ�Ƶ���ӼĴ���     
    Fdiv = (PeripheralClock / 16) / bps;        // ���ò����� 
    LPC_UART0->DLM = Fdiv / 256;
	  LPC_UART0->DLL = Fdiv % 256;
    LPC_UART0->LCR = 0x03;                      // ��ֹ���ʷ�Ƶ���ӼĴ��� 
                                                // ������Ϊ8,1,n 
	  LPC_UART0->IER = 0x05;                      // ������պͷ����ж� 
    LPC_UART0->FCR = 0x87;                      // ��ʼ��FIFO 

    NVIC_EnableIRQ(UART0_IRQn);                 // Enable UART0 interrupt 
	return 0;
}

void UART0Putch(uint8 Data)
{
    while ((LPC_UART0->LSR & 0x00000020) == 0);                                            /* UART0���ͱ��ּĴ����� */
    LPC_UART0->THR = Data;
    LPC_UART0->IER = LPC_UART0->IER | 0x02;     /* �������ж� */
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
    {                                           /* û���յ����� */
        LPC_UART0->IER = LPC_UART0->IER | 0x01; /* ��������ж� */
    }
    err = LPC_UART0->RBR;                       /* ��ȡ�յ������� */
    return err;
}

void UART0_IRQHandler (void) 
{
    uint8 IIR, temp;

    while(((IIR = LPC_UART0->IIR) & 0x01) == 0)
    {                                                   /* ���ж�δ������ */
        switch (IIR & 0x0e)
        {
            case 0x02: LPC_UART0->IER = LPC_UART0->IER & (~0x02);        /* ���пգ����ֹ�����ж� */
                break;
            case 0x04:                                  /* �������ݿ��� */
                LPC_UART0->IER = LPC_UART0->IER & (~0x01);                /* ��ֹ���ռ��ַ���ʱ�ж� */
                break;
            case 0x06:                                  /* ������״̬   */
                temp = LPC_UART0->LSR;
                break;
            case 0x0c:                                  /* �ַ���ʱָʾ */
                LPC_UART0->IER = LPC_UART0->IER & (~0x01);                /* ��ֹ���ռ��ַ���ʱ�ж� */
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
