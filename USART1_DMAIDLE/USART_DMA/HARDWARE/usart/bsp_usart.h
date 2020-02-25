#ifndef __USART_H
#define	__USART_H


#include "stm32f10x.h"
#include <stdio.h>


#define USART_RBUFF_SIZE 		 1024
#define USART_RX_DMA_CHANNEL DMA1_Channel5

extern char Usart_Rx_Buf[USART_RBUFF_SIZE] ;
extern u8 USART1_Idle_ItFlag;

void USART_Config(void);
void USART1_DMA_Config(void);
void Usart_SendByte( USART_TypeDef * pUSARTx, uint16_t ch);
void Usart_SendString( USART_TypeDef * pUSARTx, char *str,u32 length);
void Usart_SendString1( USART_TypeDef * pUSARTx, char *str);
void Usart_SendHalfWord( USART_TypeDef * pUSARTx, uint16_t ch);
void USART1_DMA_ENABLE(DMA_Channel_TypeDef* DMAy_Channelx,u8 bufSize);
#endif /* __USART_H */
