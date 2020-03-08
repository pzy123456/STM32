#include "beep.h"
#include "TIM.h"
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

//��ʼ��PB8Ϊ�����.��ʹ������ڵ�ʱ��
//��������ʼ��
void BEEP_Init(u8 vol, u16 tone)
{

    GPIO_InitTypeDef  GPIO_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��GPIOB�˿�ʱ��

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;				 //BEEP-->PB.8 �˿�����
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
    GPIO_Init(GPIOB, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8

    //GPIO_ResetBits(GPIOB, GPIO_Pin_8); //���0���رշ��������
    setBuzzerVol(vol);                                                          //���÷�����Ĭ������
    setBuzzerTone(tone);                                                        //���÷�����Ĭ������
}


/**
 * ���ܣ����÷�������������������PWM�ߵ͵�ƽ
 * ������
 *          vol:������С 0-99 0���Ǿ��� 99�����������
 * ����ֵ��None
 */
void setBuzzerVol(u8 vol)
{
    TIM_SetCompare1(TIM4, getPeriod(TIM4)*vol / 100);
}

/**
 * ���ܣ����÷�����������
 * ������
 *          tone:������С��λHz������100-10000
 *               �������Ƿ�װ��������������������ʹ��
 * ע�⣺   �������Զ�ʱ��ʱ��Ƶ��10us���м����
 * ����ֵ��None
 */
void setBuzzerTone(u16 tone)
{
    setPeriod(TIM4,100000/tone);
}

