#ifndef __SERIAL_H
#define __SERIAL_H

void Serial_Init(void);
void Serial_SendByte(uint8_t byte);
void Serial_SendString(char *String);
uint32_t Serial_Pow(uint32_t X,uint32_t Y);
void Serial_SendNumber(uint32_t Number,uint8_t Length);


#endif
