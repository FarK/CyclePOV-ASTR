#define   TASK_LEDS_C
#include  <task_leds.h>

void ISR_TIMER_SENSOR()
{
	OS_ERR err;
	CPU_INT32U time;

	if(BSP_Sensor_Event())
	{
		time = BSP_Sensor_Period();

		if(time > US_TO_TICKS(MIN_WAIT_TIME_US))
		{
			OSTaskQPost(&TLedsTCB, (void *)time, 0, OS_OPT_POST_FIFO, &err);
			BSP_Timer_Cmd(DISABLE);
		}
	}
}

void ISR_TIMER_SPOKES()
{
	OS_ERR err;

	OSTaskQPost(&TLedsTCB, (void *)0, 0, OS_OPT_POST_FIFO, &err);

	BSP_Timer_ClearIT();
}

void ISR_BUTTON()
{
	BSP_Leds_Switch();

	BSP_Button_ClearIT();
}

void TLeds(void *p_arg)
{
	OS_ERR	err;
	OS_MSG_SIZE size;
	CPU_INT32U time;

	BSP_IntVectSet(BSP_INT_ID_TIM2, 	ISR_TIMER_SENSOR);
	BSP_IntVectSet(BSP_INT_ID_TIM5, 	ISR_TIMER_SPOKES);
	BSP_IntVectSet(BSP_INT_ID_DMA1_CH5, BSP_Leds_DMA1Disable);
	BSP_IntVectSet(BSP_INT_ID_DMA2_CH5, BSP_Leds_DMA2Disable);
	BSP_IntVectSet(BSP_INT_ID_EXTI0,    ISR_BUTTON);

	BSP_Leds_ClearBuffers();
	BSP_Leds_DMAEnable();

	while(DEF_ON)
	{
		time = (CPU_INT32U)OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &size, 0, &err);

		if(time)
		{
			OSTaskQFlush(&TLedsTCB, &err);

			BSP_Timer_SetPeriod(time / NUM_SPOKES);
			BSP_Timer_Cmd(ENABLE);

			BSP_Leds_ResetSpokes();
			BSP_Leds_NextImage();
		}

		if(!BSP_Leds_NextSpoke())
		{
			BSP_Timer_Cmd(DISABLE);

			BSP_Leds_ClearBuffers();
		}

		BSP_Leds_DMAEnable();
	}
}
