#include "stm32f10x.h"                  // Device header
#include <stdio.h>

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//硬件流控制
	USART_InitStructure.USART_Mode = USART_Mode_Tx;//串口模式,接接收发送之间用或间隔
	USART_InitStructure.USART_Parity = USART_Parity_No;//校验模式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//停止位位长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStructure);

	USART_Cmd(USART1,ENABLE);
}


void Serial_SendByte(uint8_t byte)
{
	USART_SendData(USART1,byte);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(uint8_t *Array,uint16_t Length)
{
	uint16_t i;
	for(i = 0;i < Length;i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(char *String)
{
	uint8_t i;
	for(i = 0;String[i] != '\0';i++)
	{
		Serial_SendByte(String[i]);
	}
}

uint32_t Serial_Pow(uint32_t X,uint32_t Y)
{
	uint32_t Result = 1;
	while (Y--)                           //--Y
	{
		Result *= X;                //result = result * x
	}
	return Result;
}

void Serial_SendNumber(uint32_t Number,uint8_t Length)
{
	uint8_t i;
	for(i = 0;i < Length;i++)
	{
		Serial_SendByte(Number / Serial_Pow(10,Length - i - 1) % 10 + '0');
	}
}

int fputc(int ch,FILE *f)
{
	Serial_SendByte(ch);
	return ch;
}

