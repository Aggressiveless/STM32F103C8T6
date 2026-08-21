#include "stm32f10x.h"                  // Device header
#include "Motor.h"
#include "OLED.h"
#include "PWM.h"

float AimTemp = 20.0;


int16_t FanModule(uint8_t KeyNum)  //手动挡转速调节模块
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

void AutoMode(uint8_t KeyNum,float Temp)
{
//	GPIO_SetBits(GPIOA,GPIO_Pin_11);
	
	if(KeyNum == 2)
	{
		Motor_Turn();
		return;
	}
	
	
	if(KeyNum == 3)
	{
		if(AimTemp < 50)
		{
			AimTemp++;
		}
		else
		{
			OLED_ShowCN(3,1,10,1);    //“超出可预设范围”显示
			OLED_ShowCN(3,2,11,1);   
			OLED_ShowCN(3,3,12,1);
			OLED_ShowCN(3,4,13,1);
			OLED_ShowCN(3,5,14,1);
			OLED_ShowCN(3,6,15,1);
			OLED_ShowCN(3,7,16,1);
		}
	}
	if(KeyNum == 4)
	{
		if(AimTemp > 0)
		{
			AimTemp--;
		}
		else
		{
			OLED_ShowCN(4,1,10,1);    //“超出可预设范围”显示
			OLED_ShowCN(4,2,11,1);   
			OLED_ShowCN(4,3,12,1);
			OLED_ShowCN(4,4,13,1);
			OLED_ShowCN(4,5,14,1);
			OLED_ShowCN(4,6,15,1);
			OLED_ShowCN(4,7,16,1);
		}
	}
	
	if(AimTemp > 0 && AimTemp < 50)
	{
		OLED_ShowString(4,1,"                ");
	}
	
	float Error = Temp - AimTemp;
	int16_t AutoSpeed = (int16_t)(Error * 4);
	
	if(AutoSpeed > 100)
	{
		AutoSpeed = 100;
	}
	
	if(AutoSpeed < -100)
	{
		AutoSpeed = -100;
	}
	
	OLED_ShowNum(1,12,AimTemp,2);                    //目标温度显示
	OLED_ShowString(1,14,".");
	OLED_ShowNum(1,15,(uint16_t)(AimTemp * 10) % 10 ,1);
	

	OLED_ShowCN(3,1,0,1);                            //"当前转速为"显示
	OLED_ShowCN(3,2,1,1);
	OLED_ShowCN(3,3,2,1);
	OLED_ShowCN(3,4,3,1);
	OLED_ShowCN(3,5,4,1);
	OLED_ShowString(3,11,":");
	
	if(GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_11) == 1)
	{	
		OLED_ShowSignedNum(3,12,AutoSpeed,3);            //转速显示
	}
	else 
	{
		OLED_ShowSignedNum(3,12,0,3);
	}
	
	
	
	
	Motor_SetSpeed(AutoSpeed);
	
	
 
	
}

