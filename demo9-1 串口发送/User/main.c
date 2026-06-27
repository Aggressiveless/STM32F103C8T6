#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h" 


int main(void)
{

	OLED_Init();
	
	Serial_Init();
	
	Serial_SendByte(0x41);
 	
	uint8_t MyArray[]= {0x42,0x43,0x44,0x45};
	
	Serial_SendArray(MyArray,4);
	while(1)
	{

	}
}
