#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"
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
//蜂鸣器端口定义
#define BEEP PBout(8)	// BEEP,蜂鸣器接口	

/********音量*************/
typedef enum
{
    MAXVOL = 100,  //最大音量
    MUTE   = 0,   //静音
} BUZEER_VOL;


void setBuzzerVol(u8 vol);
void BEEP_Init(u8 vol, u16 tone);
void setBuzzerTone(u16 tone);
#endif

