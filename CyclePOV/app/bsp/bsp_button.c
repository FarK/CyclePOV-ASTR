#define   BSP_BUTTON_C
#include  <bsp_button.h>

void BSP_Button_Init()
{
	GPIO_InitTypeDef GPIOInit;
	EXTI_InitTypeDef EXTIInit;
	NVIC_InitTypeDef NVICInit;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

	GPIO_StructInit(&GPIOInit);
	GPIOInit.GPIO_Pin = GPIO_Pin_0;
	GPIOInit.GPIO_Mode = GPIO_Mode_IN;
	GPIOInit.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIOInit);

	EXTI_StructInit(&EXTIInit);
	EXTIInit.EXTI_Line = EXTI_Line0;
	EXTIInit.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTIInit.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTIInit.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTIInit);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	NVICInit.NVIC_IRQChannel = EXTI0_IRQn;
	NVICInit.NVIC_IRQChannelPreemptionPriority = 4;
	NVICInit.NVIC_IRQChannelSubPriority = 0;
	NVICInit.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVICInit);
}

void BSP_Button_ClearIT()
{
	EXTI_ClearITPendingBit(EXTI_Line0);
}
