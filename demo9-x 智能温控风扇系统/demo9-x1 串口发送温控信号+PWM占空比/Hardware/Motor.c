#include "stm32f10x.h"                  // Device header
#include "PWM.h"
#include "OLED.h"

int16_t Speed;

void Motor_Init(void)
{
	PWM_Init();
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
}

void Motor_SetSpeed(int16_t Speed)
{
	int16_t ActualSpeed = Speed * 0.6; //避免峰值电流过大导致转接器电流过载自动断电
	if(Speed >= 0)
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_5);
		GPIO_ResetBits(GPIOA,GPIO_Pin_4);
		PWM_SetCompare3(ActualSpeed);
	}
	else
	{
		GPIO_SetBits(GPIOA,GPIO_Pin_4);
		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		PWM_SetCompare3(-ActualSpeed);
	}
}

void Motor_Turn(void)
{
	if (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
	{
		GPIO_SetBits(GPIOA, GPIO_Pin_11);                      //通电
		OLED_ShowString(3,12,"   ");
		OLED_ShowSignedNum(3,12,Speed,3);                      //显示转速
//		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 1)
//		{
			Motor_SetSpeed(Speed);
//		}
	}
	else
	{
//		if(Speed != 0)
//		{
//			Motor_SetSpeed(Speed);
//		}
//		else
//		{
			GPIO_ResetBits(GPIOA, GPIO_Pin_11);                 //断电
			OLED_ShowString(3,12,"   ");
			OLED_ShowSignedNum(3,12,0,3);                       //转速显示0
//			if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
//			{
//				Motor_SetSpeed(0);
//			}
//		}

	}
}

