#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"
#include "Key.h"



uint8_t i;
uint16_t Speed;

int main(void)
{

	OLED_Init();
	Motor_Init();
	Key_Init();
	
	Motor_SetSpeed(20);
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Motor_Turn();
		}
		
		if(KeyNum == 2)
		{
			if(Speed < 100)
			{
				Speed += 20;
			}
			else
			{
				Speed = 0;
			}
			Motor_SetSpeed(Speed);
		}
	}
}
