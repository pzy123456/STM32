#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"
#include "rtc.h"
#include "beep.h"
#include "TIM.h"

/************************************************
 实验平台：ALIENTEK 战舰STM32F103开发板实验13
 功能：TFTLCD显示实时时间日历实验，
       KEY0键进行设置时间
       KEY1键进行设置闹钟
       闹钟到了，开始叫1分钟，关了按任意键
 作者：pzy
  Bug：硬件平台发射极和基级不能有电阻
 日期：2020/2/25
************************************************/

int main(void)
{
    u8 x = 0;
    u8 key;
    u8 time_cnt = 0;
    u8 alarm_cnt = 0;
    u8 alarm_en_cnt = 0;
  
    u8 lcd_id[12];			//存放LCD ID字符串
    delay_init();	    	 //延时函数初始化
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //设置NVIC中断分组2:2位抢占优先级，2位响应优先级
    uart_init(115200);	 	//串口初始化为115200
    LED_Init();			     //LED端口初始化
    LCD_Init();
    KEY_Init();
 
    /* 设置PWM信号,psc为719，perid为100，f = 72M/(arr+1)*(psc+1),T = 1ms，f = 1khz */
    initTIMx(TIM4, 719, 100, TIM_IT_Update | TIM_IT_CC1, DISABLE);
    /* 预装载值使能 */
    TIM_ARRPreloadConfig(TIM4, ENABLE);
     /* 占空比为90/100 = 90% */
    initTIM4OC3(90); 
  
    BEEP_Init(MUTE, 1000);
    if(initRTC() == 1)
    {
        printf("RTC init\r\n");
        configMode(TIME_MODE, &calendar);
    }
    
        POINT_COLOR = RED;
        sprintf((char*)lcd_id, "LCD ID:%04X", lcddev.id); //将LCD ID打印到lcd_id数组。
        
        
    while(1)
    {
          setBuzzerVol(MAXVOL);
          delay_ms(100);
      
         key = KEY_Scan(0);
        /*按下KEY0进入时间设置模式*/
        if(key == KEY0_PRES)
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
        
         /*按下KEY1进入闹钟设置模式*/
        if(key == KEY1_PRES)
        {
            if(++alarm_cnt == 1)
            {
                printf("into alarm mode\n");
                alarm_cnt = 0;
                configMode(ALARM_MODE, &calendar);
            }
        }
        else
        {
            alarm_cnt = 0;
        }
        
         /*按下KEY2实现关闭或开启闹钟*/
        if(key == KEY2_PRES)
        {
            if(++alarm_en_cnt == 1)
            {
                printf("start alarm mode\n");
                alarm_en_cnt = 0;
                calendar.AlarmEN ^= 1;
                enableAlarm(calendar.AlarmEN, &calendar);
            }
        }
        else
        {
            alarm_en_cnt = 0;
        }
        
        /*轮训判断，闹钟提醒,按任意键停止闹钟,或者鸣叫1分钟*/
        if(RTC_GetFlagStatus(RTC_FLAG_ALR) == SET)
        {
            alarm_en_cnt = 0;

            /*人为关掉闹钟提醒后者提醒超过1分钟后退出*/
            while(!(key == WKUP_PRES) && ++alarm_en_cnt < 20)
            {
                
                setBuzzerVol(MAXVOL);
                delay_ms(100);
                setBuzzerVol(MUTE);
                delay_ms(100);
                setBuzzerVol(MAXVOL);
                delay_ms(100);
                setBuzzerVol(MUTE);
                delay_ms(1000);                 
            }
           
            alarm_en_cnt = 0;
            setBuzzerVol(MUTE);
            RTC_WaitForLastTask();
            RTC_EnterConfigMode();
            RTC_ClearITPendingBit(RTC_FLAG_ALR);  //软件清除闹钟中断标志位
            RTC_ExitConfigMode();
            RTC_WaitForLastTask();
            updateAlarm(&calendar);
        }
        
         //BEEP = 1;
        POINT_COLOR = BLACK;
        LCD_ShowString(30, 40, 200, 24, 24, "WarShip STM32 ^_^");
        LCD_ShowString(30, 70, 200, 16, 16, "calendar_alarm clock TEST");
        LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
        LCD_ShowString(30, 110, 200, 16, 16, lcd_id);		//显示LCD ID
        x++;

        if(x == 12)x = 0;

        LED0 = !LED0;
        delay_ms(1000);

    }
}
