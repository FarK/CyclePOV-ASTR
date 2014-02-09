#define   BSP_TIMER_C
#include  <bsp_timer.h>

TIM_TimeBaseInitTypeDef TIMInit;

void BSP_Timer_Init()
{
	NVIC_InitTypeDef NVICInit;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, ENABLE);

	NVICInit.NVIC_IRQChannel = TIM5_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 2;
	NVICInit.NVIC_IRQChannelSubPriority = 0;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICInit);

	TIM_TimeBaseStructInit(&TIMInit);
	TIMInit.TIM_Prescaler = 0;
	TIMInit.TIM_CounterMode = TIM_CounterMode_Up;
	TIMInit.TIM_Period = 0;
	TIMInit.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInit(TIM5, &TIMInit);

	TIM_InternalClockConfig(TIM5);
}

void BSP_Timer_SetPeriod(uint32_t period)
{
	TIMInit.TIM_Period = period;
	TIM_TimeBaseInit(TIM5, &TIMInit);
}

void BSP_Timer_Cmd(FunctionalState state)
{
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);

	TIM_ITConfig(TIM5, TIM_IT_Update, state);
	TIM_Cmd(TIM5, state);

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}

void BSP_Timer_ClearIT()
{
	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
}
