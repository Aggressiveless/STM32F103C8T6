#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"
#include "Motor.h"
#include "Integration.h"





int main(void)
{

	Serial_Init();
	OLED_Init();
	AD_Init();
	Key_Init();
	Motor_Init();
	
 	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:00.0");
	Motor_SetSpeed(50);
	while(1)
	{
		KeyNum = Key_GetNum();

		Temp_Modude(KeyNum);

		if(KeyNum == 2)
		{
			Motor_Turn();
		}
		
		
		
//		if (Temp >=  20)
//		{
//			Motor_SetSpeed();
//		}
		
	}
}
