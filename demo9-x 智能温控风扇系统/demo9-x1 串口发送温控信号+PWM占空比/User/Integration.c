#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"
#include "Motor.h"
#include "FanModule.h"
#include "PWM.h"


uint8_t KeyNum;
uint16_t Num = 0;



void TempDis_Modude(uint16_t KeyNum,float Temp)
{
	
	if(KeyNum == 1)
	{
		OLED_ShowNum(1,9,ADValue,4);
		OLED_ShowNum(2,13,Temp,2);
		OLED_ShowString(2,15,".");
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
	OLED_ShowString(1,1,"                ");
	OLED_ShowString(2,1,"                ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:00.0");
	OLED_ShowCN(3,1,0,1);                            //"当前转速为"显示
	OLED_ShowCN(3,2,1,1);
	OLED_ShowCN(3,3,2,1);
	OLED_ShowCN(3,4,3,1);
	OLED_ShowCN(3,5,4,1);
	OLED_ShowString(3,11,":");
	TempDis_Modude(KeyNum,Temp);

	
	FanModule(KeyNum);
	
}

void ShowSP1(void)
{
	OLED_ShowString(1,1,"                ");
	OLED_ShowString(2,1,"                ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:");
	OLED_ShowCN(3,1,0,1);
	OLED_ShowCN(3,2,1,1);
	OLED_ShowCN(3,3,2,1);
	OLED_ShowCN(3,4,3,1);
	OLED_ShowCN(3,5,4,1);
	OLED_ShowString(3,11,":");
	do
	{
		TempDis_Modude(KeyNum,Temp);

		FanModule(KeyNum);
		
		KeyNum = Key_GetNum();
	}
	while(KeyNum != 5);
}

void ShowP2(void)
{
	OLED_ShowString(1,1,"                ");
	OLED_ShowString(2,1,"                ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowCN(1,1,5,1);               //“目标温度为”显示
	OLED_ShowCN(1,2,6,1);
	OLED_ShowCN(1,3,7,1);
	OLED_ShowCN(1,4,8,1);                
	OLED_ShowCN(1,5,9,1);
	OLED_ShowString(1,11,":");
}

void ShowSP2(void)
{
	OLED_ShowString(1,1,"                ");
	OLED_ShowString(2,1,"                ");
	OLED_ShowString(3,1,"                ");
	OLED_ShowCN(1,1,5,1);
	OLED_ShowCN(1,2,6,1);                            //“目标温度为”显示
	OLED_ShowCN(1,3,7,1);
	OLED_ShowCN(1,4,8,1);
	OLED_ShowCN(1,5,9,1);
	OLED_ShowString(1,11,":");
	
	OLED_ShowCN(2,1,0,1);                            //"当前温度为"显示
	OLED_ShowCN(2,2,1,1);
	OLED_ShowCN(2,3,7,1);
	OLED_ShowCN(2,4,8,1);
	OLED_ShowCN(2,5,4,1);
	OLED_ShowString(2,11,":");
	
	do
	{
		Temp = GetTemp();
		OLED_ShowNum(2,13,Temp,2);
		OLED_ShowString(2,15,".");
		OLED_ShowNum(2,16,(uint16_t)(Temp * 10) % 10 ,1);
		
		AutoMode(KeyNum,Temp);
		KeyNum = Key_GetNum();
	}
	while(KeyNum != 5);
}
 
void TurnPage(uint8_t KeyNum)
{
	if(KeyNum == 5)
	{
		Num++;
		if(Num % 2 == 1)
		{
			ShowSP2();
		}
		else
		{
			ShowSP1();
		}
//		return;
	}
	
	
}

void Display(uint16_t Num)
{
	if(Num % 2 == 1)
	{
		ShowSP2();
	}
	else
	{
		ShowSP1();
	}
}





