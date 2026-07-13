#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key.h"
#include "OLED.h"


uint8_t KeyNum;


int main(void)
{
	LED_Init();
	Key_Init();
	OLED_Init();
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if(KeyNum == 1)
		{
			LED1_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_1) == SET)
			{
				OLED_ShowString(1,1,"        ");
				OLED_ShowString(1,1,"LED1_ON");
			}
			else
			{
				OLED_ShowString(1,1,"        ");
				OLED_ShowString(1,1,"LED1_OFF");
			}
		}
		
		
		if(KeyNum == 2)
		{
			LED2_Turn();
			if(GPIO_ReadOutputDataBit(GPIOA,GPIO_Pin_2) == SET)
			{
				OLED_ShowString(2,1,"        ");
				OLED_ShowString(2,1,"LED2_ON");
			}
			else
			{
				OLED_ShowString(2,1,"        ");
				OLED_ShowString(2,1,"LED2_OFF");
			}
		}
		
		
	}
}
