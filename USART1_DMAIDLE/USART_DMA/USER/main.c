#include "led.h"
#include "sys.h"
#include "delay.h"
#include "bsp_usart.h"
/******************************************************************
 * 文件：main.c
 * 描述：串口接收不定长数据,UART+DMA
 * 日期：2020-02-25
 * 作者：pzy
 * 版本：Ver.1.0 | 最初版本
*******************************************************************/   



int main()
{
		LED_Init();
		USART_Config();
		USART1_DMA_Config();
		while(1)
		{
			
		}
}


