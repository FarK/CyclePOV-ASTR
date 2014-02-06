#define   TASKS_C
#include  <tasks.h>

void AppObjCreate (void)
{

}

void AppTaskCreate (void)
{
	OS_ERR err;

	OSTaskCreate((OS_TCB     *)&TLedsTCB,
				 (CPU_CHAR   *)"LEDS",
				 (OS_TASK_PTR )TLeds,
				 (void       *)0,
				 (OS_PRIO     )TASK_LEDS_PRIORITY,
				 (CPU_STK    *)&TLedsStk[0],
				 (CPU_STK_SIZE)TASK_LEDS_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_LEDS_STK_SIZE,
				 (OS_MSG_QTY  )16,
				 (OS_TICK     )0,
				 (void       *)0,
				 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 (OS_ERR     *)&err);

	if(err != OS_ERR_NONE)
	{

	}
}
