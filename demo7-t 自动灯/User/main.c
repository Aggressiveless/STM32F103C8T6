#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ADValue;
uint16_t Brightness;

int main(void)
{

	OLED_Init();
	AD_Init();

	
 	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Ambient");
	OLED_ShowString(3,1,"Brightness");

	while(1)
	{
		ADValue = AD_GetValue();
		Brightness = (100 - (float)ADValue / 4095 * 100);
		OLED_ShowNum(1,9,ADValue,4);
		OLED_ShowNum(4,1,Brightness,3);
		
		Delay_ms(100);
	}
}
