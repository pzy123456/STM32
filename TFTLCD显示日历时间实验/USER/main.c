#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "rtc.h"



/************************************************
 实验平台：ALIENTEK 战舰STM32F103开发板实验13
 功能：TFTLCD显示实时时间日历实验，KEY0键进行设置时间
 作者：pzy
 日期：2020/2/25
************************************************/

int main(void)
{
    u8 x = 0;
    u8 time_cnt = 0;
    u8 lcd_id[12];			//存放LCD ID字符串
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
    LED_Init();			     //LED端口初始化
    LCD_Init();
    KEY_Init();

    if(initRTC() == 1)
    {
        printf("RTC init\r\n");
        configMode(TIME_MODE, &calendar);
    }

        POINT_COLOR = RED;
        sprintf((char*)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。

    while(1)
    {
        /*长按UP键两秒进入时间设置模式*/
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
        LCD_ShowString(30, 110, 200, 16, 16, lcd_id);		//显示LCD ID
        LCD_ShowString(30, 130, 200, 12, 12, "2019/9/29");
        x++;

        if(x == 12)x = 0;

        LED0 = !LED0;
        delay_ms(1000);

    }
}
