/**
  ******************************************************************************
  * @file    bsp_usart.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �ض���c��printf������usart�˿�
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ��STM32 F103-MINI ������  
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */ 
	
#include "bsp_usart.h"

 /**
  * @brief  ����Ƕ�������жϿ�����NVIC
  * @param  ��
  * @retval ��
  */
char Usart_Rx_Buf[USART_RBUFF_SIZE] = {0};

static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;
  
  /* Ƕ�������жϿ�������ѡ�� */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����USART1Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  /* �������ȼ�*/
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  /* �����ȼ� */
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
  /* ʹ���ж� */
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  /* ��ʼ������NVIC */
  NVIC_Init(&NVIC_InitStructure);
	
}

 /**
  * @brief  USART GPIO ����,������������
  * @param  ��
  * @retval ��
  */


void USART_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	// �򿪴���GPIO��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// �򿪴���1�����ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	// ��USART1 Tx��GPIO����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

  // ��USART1 Rx��GPIO����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// ���ô��ڵĹ�������
	// ���ò�����
	USART_InitStructure.USART_BaudRate = 115200;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl = 
	USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART1, &USART_InitStructure);
	// �����ж����ȼ�����
	NVIC_Configuration();
	
	/* CPU��Сȱ�ݣ��������úã����ֱ��Send�����1���ֽڷ��Ͳ���ȥ

	�����������1���ֽ��޷���ȷ���ͳ�ȥ������ 
	*/
	
	USART_ITConfig(USART1,USART_IT_IDLE,ENABLE);	
	USART_DMACmd(USART1,USART_DMAReq_Rx,ENABLE);  
	// ʹ�ܴ���
	USART_Cmd(USART1, ENABLE);	
}


void USART1_DMA_Config(void)
{
		DMA_InitTypeDef DMA_InitStructure;
	
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);  
    //DMA1ͨ��5����  
    DMA_DeInit(USART_RX_DMA_CHANNEL);  
    //�����ַ  
    DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)(&USART1->DR);  
    //�ڴ��ַ  
    DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)Usart_Rx_Buf;  
    //dma���䷽����  
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  
    //����DMA�ڴ���ʱ�������ĳ���  
    DMA_InitStructure.DMA_BufferSize = USART_RBUFF_SIZE;  
    //����DMA���������ģʽ��һ������  
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  
    //����DMA���ڴ����ģʽ  
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  
    //���������ֳ�  
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;  
    //�ڴ������ֳ�  
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;  
    //����DMA�Ĵ���ģʽ  
    DMA_InitStructure.DMA_Mode = DMA_Mode_Normal;  
    //����DMA�����ȼ���  
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;  
    //����DMA��2��memory�еı����������  
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  
    DMA_Init(DMA1_Channel5,&DMA_InitStructure);  
		DMA_SetCurrDataCounter(DMA1_Channel5, USART_RBUFF_SIZE);
	  
    DMA_ITConfig(USART_RX_DMA_CHANNEL, DMA_IT_TC, ENABLE);
    //ʹ��ͨ��5  
    DMA_Cmd(USART_RX_DMA_CHANNEL,ENABLE);  
}



/*****************  ����һ���ֽ� **********************/
void Usart_SendByte( USART_TypeDef * USARTx, uint16_t ch)
{
	/* ����һ���ֽ����ݵ�USART */
	USART_SendData(USARTx,ch);
		
	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET);	
}

/****************** ����8λ������ ************************/
void Usart_SendArray( USART_TypeDef * pUSARTx, uint8_t *array, uint16_t num)
{
  uint8_t i;
	
	for(i=0; i<num; i++)
  {
	    /* ����һ���ֽ����ݵ�USART */
	    Usart_SendByte(pUSARTx,array[i]);	
  
  }
	/* �ȴ�������� */
	while(USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET);
}

/*****************  �����ַ��� **********************/
void Usart_SendString( USART_TypeDef * pUSARTx, char *str,u32 length)
{
		while(length)//������������⣬�����ֵΪ0ʱ�����while�Ͳ�ѭ���ˣ����൱��while(0)
		{
			Usart_SendByte(USART1,*str++); 
			length -- ;	
		}
}
void Usart_SendString1( USART_TypeDef * pUSARTx, char *str)
{
	while(*str)
	{
		Usart_SendByte(USART1,*str++); 
	}
}
/*****************  ����һ��16λ�� **********************/
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch)
{
	uint8_t temp_h, temp_l;
	
	/* ȡ���߰�λ */
	temp_h = (ch&0XFF00)>>8;
	/* ȡ���Ͱ�λ */
	temp_l = ch&0XFF;
	
	/* ���͸߰�λ */
	USART_SendData(pUSARTx,temp_h);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
	
	/* ���͵Ͱ�λ */
	USART_SendData(pUSARTx,temp_l);	
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);	
}

///�ض���c�⺯��printf�����ڣ��ض�����ʹ��printf����
int fputc(int ch, FILE *f)
{
		/* ����һ���ֽ����ݵ����� */
		USART_SendData(USART1, (uint8_t) ch);
		
		/* �ȴ�������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);		
	
		return (ch);
}

///�ض���c�⺯��scanf�����ڣ���д����ʹ��scanf��getchar�Ⱥ���
int fgetc(FILE *f)
{
		/* �ȴ������������� */
		while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

		return (int)USART_ReceiveData(USART1);
}

