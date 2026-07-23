#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	//重映射
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);

	//GPIO初始化
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStructure);
	
	
	/*?????*/
	TIM_InternalClockConfig(TIM2);		//??TIM2?????,???????,TIM????????
	
	//时基单元初始化
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;				//???????
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;		//????,?????,????????????,?????????
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;	//?????,??????
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;				//ARR重装值
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;				//预分频器
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;			//?????,?????????
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);				//????????TIM_TimeBaseInit,??TIM2?????	
	
	
	//输出比较初始化（PWM）
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //设置输出比较模式
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCPolarity_High;//设置 极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //设置使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置CCR
	TIM_OC3Init(TIM2,&TIM_OCInitStructure);
	
	
	
	/*TIM??*/
	TIM_Cmd(TIM2, ENABLE);			//??TIM2,???????
}


void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2,Compare);
}



