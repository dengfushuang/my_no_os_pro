#ifndef __USER_CONFIG_H
#define __USER_CONFIG_H
/**************ϵͳͷ�ļ�***************/
#include "lpc17xx_conf.h"
/**************�û�ͷ�ļ�***************/
#include "uart0.h"

#define RUN_LED_INIT LPC_GPIO3->DIR = (1u<<3)
#define RUN_LED_ON   LPC_GPIO3->CLR |= (1u<<3)
#define RUN_LED_OFF   LPC_GPIO3->SET |= (1u<<3)

#endif
