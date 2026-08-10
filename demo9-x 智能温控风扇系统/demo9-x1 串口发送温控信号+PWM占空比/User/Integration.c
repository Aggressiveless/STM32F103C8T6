#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"
#include "Motor.h"
#include "FanModule.h"

uint16_t ADValue;
uint8_t KeyNum;
float Temp;



void TempDis_Modude(uint16_t KeyNum)
{
	ADValue = AD_GetValue();
	Temp = (float)(4096 - ADValue) / 4095 * 100.0 - 28.0;


	
		if(KeyNum == 1)
		{
			OLED_ShowNum(1,9,ADValue,4);
			OLED_ShowNum(2,13,Temp,2);
			OLED_ShowNum(2,16,(uint16_t)(Temp * 10) % 10 ,1);
			
			Serial_SendString("当前温度是:");
			Serial_SendNumber(Temp,2);
			Serial_SendString(".");
			Serial_SendNumber((uint16_t)(Temp * 10) % 10,1);
			Serial_SendString("\r\n");
			

		}
}

void ShowP1(void)
{
	
	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:00.0");
	OLED_ShowCN(3,1,0,1);
	OLED_ShowCN(3,2,1,1);
	OLED_ShowCN(3,3,2,1);
	OLED_ShowCN(3,4,3,1);
	OLED_ShowCN(3,5,4,1);
	
	FanModule(KeyNum);
	if(KeyNum == 2)
	{
		Motor_Turn();
	}
}

void ShowP2(void)
{
	OLED_ShowString(1,1,"");
}
 
void TurnPage(uint8_t KeyNum)
{
	uint8_t Num;
	if(KeyNum == 5)
	{
		Num++;
	}
	if(Num % 2 == 1)
	{
		ShowP1();
	}
	else
	{
		ShowP2();
	}
}
