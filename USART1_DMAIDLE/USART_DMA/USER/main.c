#include "led.h"
#include "sys.h"
#include "delay.h"
#include "bsp_usart.h"
/******************************************************************
 * �ļ���main.c
 * ���������ڽ��ղ���������,UART+DMA
 * ���ڣ�2020-02-25
 * ���ߣ�pzy
 * �汾��Ver.1.0 | ����汾
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


