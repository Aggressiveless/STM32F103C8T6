#ifndef __OLED_H
#define __OLED_H

#include "main.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64

#define u8  unsigned char
#define u32 unsigned int

/*
 * OLED software I2C pin mapping, converted from the original HAL project:
 *   SCL -> PB3
 *   SDA -> PB4
 *
 * PB3/PB4 are JTAG pins by default on STM32F103, so main.c disables JTAG
 * while keeping SWD. If your own board wires OLED to PB8/PB9, change the
 * GPIO port/pin macros below and the GPIO_Config() pins in User/main.c.
 */
#define OLED_GPIO_PORT GPIOB
#define OLED_SCL_PIN   GPIO_Pin_3
#define OLED_SDA_PIN   GPIO_Pin_4

#define OLED_SCLK_Clr() GPIO_ResetBits(OLED_GPIO_PORT, OLED_SCL_PIN)
#define OLED_SCLK_Set() GPIO_SetBits(OLED_GPIO_PORT, OLED_SCL_PIN)

#define OLED_SDIN_Clr() GPIO_ResetBits(OLED_GPIO_PORT, OLED_SDA_PIN)
#define OLED_SDIN_Set() GPIO_SetBits(OLED_GPIO_PORT, OLED_SDA_PIN)

#define OLED_CMD  0
#define OLED_DATA 1

void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_DisplayOn(void);
void OLED_DisplayOff(void);
void OLED_Init(void);
void OLED_Clear(void);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);
void OLED_SetPos(unsigned char x, unsigned char y);

void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Delay_50ms(unsigned int Del_50ms);
void Delay_1ms(unsigned int Del_1ms);
void OLED_FillPicture(unsigned char fill_Data);
void Picture(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_WriteCommand(unsigned char IIC_Command);
void IIC_WriteData(unsigned char IIC_Data);
void IIC_WriteByte(unsigned char IIC_Byte);
void IIC_WaitAck(void);

void OLED_DrawBMPFast(const unsigned char BMP[]);
void OLED_DrawGround(void);
void OLED_DrawCloud(void);
void OLED_DrawDino(void);
void OLED_DrawCactus(void);
int OLED_DrawDinoJump(char reset);
int OLED_DrawCactusRandom(unsigned char ver, unsigned char reset);
void OLED_DrawRestart(void);
void OLED_DrawCover(void);

#endif
