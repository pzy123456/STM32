#ifndef __BEEP_H
#define __BEEP_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//��������������
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/2
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved
//////////////////////////////////////////////////////////////////////////////////
//�������˿ڶ���
#define BEEP PBout(8)	// BEEP,�������ӿ�	

/********����*************/
typedef enum
{
    MAXVOL = 100,  //�������
    MUTE   = 0,   //����
} BUZEER_VOL;


void setBuzzerVol(u8 vol);
void BEEP_Init(u8 vol, u16 tone);
void setBuzzerTone(u16 tone);
#endif

