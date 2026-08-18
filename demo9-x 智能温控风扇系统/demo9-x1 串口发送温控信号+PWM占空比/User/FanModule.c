#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"

uint16_t AimTemp = 20;

uint16_t FanModule(uint8_t KeyNum)
{
	if(KeyNum == 2)
	{
		Motor_Turn();
	}
	
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
			OLED_ShowSignedNum(3,12,Speed,3);//
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
	uint16_t Error = Temp - AimTemp;
	uint16_t AutoSpeed = 0;
	
	
	if(KeyNum == 3)
	{
		if(AimTemp < 50)
		{
			AimTemp++;
		}
		else
		{
			OLED_ShowCN(1,1,10,1);
			OLED_ShowCN(1,2,11,1);
			OLED_ShowCN(1,3,12,1);
			OLED_ShowCN(1,4,13,1);
			OLED_ShowCN(1,5,14,1);
			OLED_ShowCN(1,1,15,1);
			OLED_ShowCN(1,2,16,1);
			OLED_ShowString(1,11,":");
		}
	}
	if(KeyNum == 4)
	{
		if(AimTemp > 0)
		{
			AimTemp--;
		}
	}
	
	OLED_ShowNum(1,12,AimTemp,2);
	
	
	
	Motor_SetSpeed(Error);
	
	
 
	
}

