#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"

uint16_t AimTemp;

uint16_t FanModule(uint8_t KeyNum)
{
	if(KeyNum == 3)
	{
		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
		{
			GPIO_SetBits(GPIOA,GPIO_Pin_11);
			Speed = 20;
			Motor_SetSpeed(Speed);
			OLED_ShowSignedNum(3,12,Speed,3);//
			return Speed;
		}
		if(Speed <= 100)
		{
			Speed += 20;
			if(Speed > 100)
			{
				Speed = 100;
			}
		}
		else
		{
			Speed = 0;
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(3,12,Speed,3);
	}
	
	if(KeyNum == 4)
	{
		if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 0)
			{
				GPIO_SetBits(GPIOA,GPIO_Pin_11);
				Speed = -20;
				Motor_SetSpeed(Speed);
				OLED_ShowNum(3,12,Speed,3);//
				return Speed;
			}
			if(Speed >= -100)
			{
				Speed -= 20;
				if(Speed < -100)
				{
					Speed = -100;
				}
			
			}
			Motor_SetSpeed(Speed);
			OLED_ShowSignedNum(3,12,Speed,3);
	}
	
	return Speed;
}

void AutoMode(uint8_t KeyNum,uint16_t Temp)
{
	if(KeyNum == 2)
	{
		
	}
}

