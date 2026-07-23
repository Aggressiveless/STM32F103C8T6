#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"



uint8_t i;
uint8_t KeyNum;


int main(void)
{

	OLED_Init();
	Motor_Init();
	Key_Init();
	
	Motor_SetSpeed(-50);
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 0)
		{
			
		}
	}
}
