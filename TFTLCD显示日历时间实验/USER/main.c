#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "rtc.h"



/************************************************
 ʵ��ƽ̨��ALIENTEK ս��STM32F103������ʵ��13
 ���ܣ�TFTLCD��ʾʵʱʱ������ʵ�飬KEY0����������ʱ��
 ���ߣ�pzy
 ���ڣ�2020/2/25
************************************************/

int main(void)
{
    u8 x = 0;
    u8 time_cnt = 0;
    u8 lcd_id[12];			//���LCD ID�ַ���
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
    LED_Init();			     //LED�˿ڳ�ʼ��
    LCD_Init();
    KEY_Init();

    if(initRTC() == 1)
    {
        printf("RTC init\r\n");
        configMode(TIME_MODE, &calendar);
    }

        POINT_COLOR = RED;
        sprintf((char*)lcd_id, "LCD ID:%04X", lcddev.id); //��LCD ID��ӡ��lcd_id���顣

    while(1)
    {
        /*����UP���������ʱ������ģʽ*/
        if(KEY_Scan(0) == KEY0_PRES)
        {
            if(++time_cnt == 1)
            {
                time_cnt = 0;
                configMode(TIME_MODE, &calendar);
            }
        }
        else
        {
            time_cnt = 0;
        }

        POINT_COLOR = BLACK;
        LCD_ShowString(30, 40, 200, 24, 24, "WarShip STM32 ^_^");
        LCD_ShowString(30, 70, 200, 16, 16, "RTC TEST");
        LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
        LCD_ShowString(30, 110, 200, 16, 16, lcd_id);		//��ʾLCD ID
        LCD_ShowString(30, 130, 200, 12, 12, "2019/9/29");
        x++;

        if(x == 12)x = 0;

        LED0 = !LED0;
        delay_ms(1000);

    }
}
