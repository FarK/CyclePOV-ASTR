#define   TASK_LEDS_C
#include  <task_leds.h>

#define US_TO_TICKS(us) (us * 80)

void ISR_TIMER_SENSOR(void)
{
	OS_ERR err;
	CPU_INT32U time = BSP_Sensor_Period();
	BSP_Timer_Enable(DISABLE);

	if(time > US_TO_TICKS(100 * 1000))
	{
		OSTaskQPost(&TLedsTCB, (void *)time, 0, OS_OPT_POST_FIFO, &err);
	}
}

void ISR_TIMER_SPOKES(void)
{
	OS_ERR err;

	TIM_ClearITPendingBit(TIM5, TIM_IT_Update);
	OSTaskQPost(&TLedsTCB, (void *)0, 0, OS_OPT_POST_FIFO, &err);

	GPIO_ToggleBits(GPIOD, GPIO_Pin_12);
}

void ISR_DMA_FINISHED(void)
{
	BSP_Leds_DMADisable();
}

#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>

void TLeds(void *p_arg)
{
	OS_ERR	err;
	OS_MSG_SIZE size;
	CPU_INT32U time;

	CPU_INT32U spoke_period;

	static CPU_INT32U current_spoke = 0;

	////////////////////////////////////////
	GPIO_InitTypeDef GPIOInit;

	// GPIO
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	GPIO_StructInit(&GPIOInit);
	GPIOInit.GPIO_Pin = GPIO_Pin_12;
	GPIOInit.GPIO_PuPd = GPIO_OType_PP;
	GPIOInit.GPIO_Mode = GPIO_Mode_OUT;
	GPIOInit.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOD, &GPIOInit);
	////////////////////////////////////////

	BSP_IntVectSet(BSP_INT_ID_TIM2, 	ISR_TIMER_SENSOR);
	BSP_IntVectSet(BSP_INT_ID_TIM5, 	ISR_TIMER_SPOKES);
	BSP_IntVectSet(BSP_INT_ID_DMA1_CH4, ISR_DMA_FINISHED);

	BSP_Leds_ClearBuffer();
	BSP_Leds_DMAEnable();

	while(DEF_ON)
	{
		time = (CPU_INT32U)OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &size, 0, &err);

		if(time)
		{
			OSTaskQFlush(&TLedsTCB, &err);

			spoke_period = time / NUM_SPOKES;

			BSP_Timer_Set_Period(spoke_period);
			BSP_Timer_Enable(ENABLE);

			current_spoke = 0;
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
		}

		BSP_Leds_DMADisable();

		if(current_spoke < NUM_SPOKES)
		{
			BSP_Leds_SetBuffer(current_spoke++);
		}
		else
		{
			BSP_Leds_ClearBuffer();
			BSP_Timer_Enable(DISABLE);
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);

			OSTaskQFlush(&TLedsTCB, &err);
		}

		BSP_Leds_DMAEnable();
	}
}
