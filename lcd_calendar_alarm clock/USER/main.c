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
 ʵ��ƽ̨��ALIENTEK ս��STM32F103������ʵ��13
 ���ܣ�TFTLCD��ʾʵʱʱ������ʵ�飬
       KEY0����������ʱ��
       KEY1��������������
       ���ӵ��ˣ���ʼ��1���ӣ����˰������
 ���ߣ�pzy
  Bug��Ӳ��ƽ̨���伫�ͻ��������е���
 ���ڣ�2020/2/25
************************************************/

int main(void)
{
    u8 x = 0;
    u8 key;
    u8 time_cnt = 0;
    u8 alarm_cnt = 0;
    u8 alarm_en_cnt = 0;
  
    u8 lcd_id[12];			//���LCD ID�ַ���
    delay_init();	    	 //��ʱ������ʼ��
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
    uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
    LED_Init();			     //LED�˿ڳ�ʼ��
    LCD_Init();
    KEY_Init();
 
    /* ����PWM�ź�,pscΪ719��peridΪ100��f = 72M/(arr+1)*(psc+1),T = 1ms��f = 1khz */
    initTIMx(TIM4, 719, 100, TIM_IT_Update | TIM_IT_CC1, DISABLE);
    /* Ԥװ��ֵʹ�� */
    TIM_ARRPreloadConfig(TIM4, ENABLE);
     /* ռ�ձ�Ϊ90/100 = 90% */
    initTIM4OC3(90); 
  
    BEEP_Init(MUTE, 1000);
    if(initRTC() == 1)
    {
        printf("RTC init\r\n");
        configMode(TIME_MODE, &calendar);
    }
    
        POINT_COLOR = RED;
        sprintf((char*)lcd_id, "LCD ID:%04X", lcddev.id); //��LCD ID��ӡ��lcd_id���顣
        
        
    while(1)
    {
          setBuzzerVol(MAXVOL);
          delay_ms(100);
      
         key = KEY_Scan(0);
        /*����KEY0����ʱ������ģʽ*/
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
        
         /*����KEY1������������ģʽ*/
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
        
         /*����KEY2ʵ�ֹرջ�������*/
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
        
        /*��ѵ�жϣ���������,�������ֹͣ����,��������1����*/
        if(RTC_GetFlagStatus(RTC_FLAG_ALR) == SET)
        {
            alarm_en_cnt = 0;

            /*��Ϊ�ص��������Ѻ������ѳ���1���Ӻ��˳�*/
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
            RTC_ClearITPendingBit(RTC_FLAG_ALR);  //�����������жϱ�־λ
            RTC_ExitConfigMode();
            RTC_WaitForLastTask();
            updateAlarm(&calendar);
        }
        
         //BEEP = 1;
        POINT_COLOR = BLACK;
        LCD_ShowString(30, 40, 200, 24, 24, "WarShip STM32 ^_^");
        LCD_ShowString(30, 70, 200, 16, 16, "calendar_alarm clock TEST");
        LCD_ShowString(30, 90, 200, 16, 16, "ATOM@ALIENTEK");
        LCD_ShowString(30, 110, 200, 16, 16, lcd_id);		//��ʾLCD ID
        x++;

        if(x == 12)x = 0;

        LED0 = !LED0;
        delay_ms(1000);

    }
}
