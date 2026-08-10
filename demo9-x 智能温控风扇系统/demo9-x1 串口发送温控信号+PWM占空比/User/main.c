#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"
#include "Serial.h"
#include "Key.h"
#include "Motor.h"
#include "Integration.h"
#include "FanModule.h" 




int main(void)
{

	Serial_Init();
	OLED_Init();
	AD_Init();
	Key_Init();
	Motor_Init();
	
 	

	Speed = 50;
	OLED_ShowString(3,11,":");
	OLED_ShowNum(3,12,000,3);
	Motor_SetSpeed(Speed);
	
	ShowP1();
	
	while(1)
	{
		KeyNum = Key_GetNum();

		TempDis_Modude(KeyNum);
		
		TurnPage(KeyNum);

		ShowP1();
		
//		OLED_ShowNum(3,12,Speed,3);

		
//		if (Temp >=  20)
//		{
//			Motor_SetSpeed();
//		}
		
	}
}
