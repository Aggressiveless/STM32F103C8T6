#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Motor.h"

uint8_t i;

int main(void)
{

	OLED_Init();
	Motor_Init();
	
	Motor_SetSpeed(50);
	while(1)
	{
	
	}
}
