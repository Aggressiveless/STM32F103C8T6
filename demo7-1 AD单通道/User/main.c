#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
<<<<<<< HEAD
#include "AD.h"

uint16_t ADValue;
float Voltage;
=======


>>>>>>> 2fc00b8badae6819aa47f4e7851369efc1eca3af

int main(void)
{

	OLED_Init();
<<<<<<< HEAD
	AD_Init();

	
 	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Voltage:0.00V");
	
	while(1)
	{
		ADValue = AD_GetValue();
		Voltage = (float)ADValue / 4095 * 3.33;
			
		OLED_ShowNum(1,9,ADValue,4);
		OLED_ShowNum(2,9,Voltage,1);
		OLED_ShowNum(2,11,(uint16_t)(Voltage * 100) % 100,2);
		
		Delay_ms(100);
=======
	
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(1,3,"HelloWorld!");
	OLED_ShowNum(2,1,114514,6);
	OLED_ShowSignedNum(2,8,-100,3);
	OLED_ShowHexNum(3,1,0xAA55,4);
	OLED_ShowBinNum(4,1,0XAA55,16);
	
	OLED_Clear();
 	
	while(1)
	{

>>>>>>> 2fc00b8badae6819aa47f4e7851369efc1eca3af
	}
}
