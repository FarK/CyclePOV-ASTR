#define   BSP_SENSOR_C
#include  <bsp_sensor.h>

// PIN A1 FOR INPUT CAPTURE
void BSP_Sensor_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;

	// GPIO CONFIG
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_TIM2);

	// NVIC CONFIG
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	// TIMER CONFIG
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	TIM_ICStructInit(&TIM_ICInitStructure);
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICFilter = 0;
	TIM_ICInit(TIM2, &TIM_ICInitStructure);

	TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);

	TIM_Cmd(TIM2, ENABLE);
}

CPU_INT32U BSP_Sensor_Period()
{
	CPU_INT32U time = 0;

	if(TIM_GetITStatus(TIM2, TIM_IT_CC2) == SET)
	{
		time = TIM_GetCapture2(TIM2);

		TIM_Cmd(TIM2, DISABLE);
		TIM_SetCounter(TIM2, 0);
		TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);
		TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);
		TIM_Cmd(TIM2, ENABLE);

//		if(TIM_GetFlagStatus(TIM2, TIM_FLAG_CC2OF) == SET)
//		{
//			// OVERCAPTURE
//			TIM_ClearFlag(TIM2, TIM_FLAG_CC2OF);
//		}
	}

	return time;
}
