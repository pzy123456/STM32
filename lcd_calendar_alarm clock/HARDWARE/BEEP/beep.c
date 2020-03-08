#include "beep.h"
#include "TIM.h"
//////////////////////////////////////////////////////////////////////////////////
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK战舰STM32开发板
//蜂鸣器驱动代码
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/2
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////

//初始化PB8为输出口.并使能这个口的时钟
//蜂鸣器初始化
void BEEP_Init(u8 vol, u16 tone)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能GPIOB端口时钟

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 端口配置
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8

    //GPIO_ResetBits(GPIOB, GPIO_Pin_8); //输出0，关闭蜂鸣器输出
    setBuzzerVol(vol);                                                          //设置蜂鸣器默认音量
    setBuzzerTone(tone);                                                        //设置蜂鸣器默认音调
}


/**
 * 功能：设置蜂鸣器的音量，产生用PWM高低电平
 * 参数：
 *          vol:音量大小 0-99 0就是静音 99就是最大音量
 * 返回值：None
 */
void setBuzzerVol(u8 vol)
{
    TIM_SetCompare1(TIM4, getPeriod(TIM4)*vol / 100);
}

/**
 * 功能：设置蜂鸣器的音调
 * 参数：
 *          tone:音调大小单位Hz，建议100-10000
 *               另外我们封装了七音阶音调，方便大家使用
 * 注意：   这里是以定时器时钟频率10us进行计算的
 * 返回值：None
 */
void setBuzzerTone(u16 tone)
{
    setPeriod(TIM4,100000/tone);
}

