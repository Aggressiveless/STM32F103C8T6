#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"

uint16_t ADValue;
uint8_t KeyNum;
float Temp;

int main(void)
{

	Serial_Init();
	OLED_Init();
	AD_Init();
	Key_Init();
	
 	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:00.0");
	while(1)
	{
		KeyNum = Key_GetNum();

		
		ADValue = AD_GetValue();
		Temp = (float)(4096 - ADValue) / 4095 * 100.0 - 20.0;

		if(KeyNum == 1)
		{
			OLED_ShowNum(1,9,ADValue,4);
			OLED_ShowNum(2,13,Temp,2);
			OLED_ShowNum(2,16,(uint16_t)(Temp * 10) % 10 ,1);
			OLED_ShowNum(3,1,(float)Temp,4);
			
			Serial_SendString("当前温度是：");
			Serial_SendNumber(Temp,2);
			Serial_SendString(".");
			Serial_SendNumber((uint16_t)(Temp * 10) % 10,1);
			Serial_SendString("\r\n");
		}
		
		if (Temp >=  20)
		{
			PWM_SetCompare1();
		}
		
	}
}
