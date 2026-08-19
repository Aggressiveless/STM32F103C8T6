#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare);
uint16_t GetTemp(uint16_t AD_);

extern uint16_t Temp;
extern uint16_t ADValue;









#endif
