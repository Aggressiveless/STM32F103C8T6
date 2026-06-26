#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h" 


int main(void)
{

	OLED_Init();
	
	Serial_Init();
	
	Serial_SendByte(0x41);
 	
	while(1)
	{

	}
}
