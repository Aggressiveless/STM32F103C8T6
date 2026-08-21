#ifndef __PWM_H
#define __PWM_H

void PWM_Init(void);
void PWM_SetCompare3(uint16_t Compare);
float GetTemp(void);

extern float Temp;
extern uint16_t ADValue;









#endif
