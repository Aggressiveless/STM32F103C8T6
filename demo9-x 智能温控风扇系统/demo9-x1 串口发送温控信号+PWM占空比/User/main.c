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
	
 	OLED_ShowString(1,1,"ADValue:");
	OLED_ShowString(2,1,"Temperature:00.0");
	OLED_ShowCN(3,1,0,1);
	OLED_ShowCN(3,2,1,1);
	OLED_ShowCN(3,3,2,1);
	OLED_ShowCN(3,4,3,1);
	OLED_ShowCN(3,5,4,1);

	Speed = 50;
	OLED_ShowString(3,11,":");
	OLED_ShowNum(3,12,000,3);
	Motor_SetSpeed(Speed);
	while(1)
	{
		KeyNum = Key_GetNum();

		Display_Modude(KeyNum);

		FanModule(KeyNum);
		if(KeyNum == 2)
		{
			Motor_Turn();
		}
		
//		OLED_ShowNum(3,12,Speed,3);

		
//		if (Temp >=  20)
//		{
//			Motor_SetSpeed();
//		}
		
	}
}
