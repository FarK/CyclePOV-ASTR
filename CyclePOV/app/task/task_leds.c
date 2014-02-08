#define   TASK_LEDS_C
#include  <task_leds.h>

void ISR_TIMER_SENSOR(void)
{
	OS_ERR err;
	CPU_INT32U time = BSP_Sensor_Period();
	BSP_Timer_Enable(DISABLE);

	if(time > US_TO_TICKS(MIN_WAIT_TIME_US))
	{
		OSTaskQPost(&TLedsTCB, (void *)time, 0, OS_OPT_POST_FIFO, &err);
	}
}

void ISR_TIMER_SPOKES(void)
{
	OS_ERR err;

	OSTaskQPost(&TLedsTCB, (void *)0, 0, OS_OPT_POST_FIFO, &err);
	BSP_Timer_Enable(DISABLE);
}

void ISR_DMA_FINISHED(void)
{
	BSP_Leds_DMADisable();
}

void TLeds(void *p_arg)
{
	OS_ERR	err;
	OS_MSG_SIZE size;
	CPU_INT32U time;

	static CPU_INT32U current_spoke = 0;

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
			BSP_Timer_Set_Period(time / NUM_SPOKES);

			current_spoke = 0;
		}

		BSP_Leds_DMADisable();

		if(current_spoke < NUM_SPOKES)
		{
			BSP_Leds_SetBuffer(current_spoke++);
			BSP_Timer_Enable(ENABLE);
		}
		else
		{
			BSP_Leds_ClearBuffer();
		}

		BSP_Leds_DMAEnable();
	}
}
