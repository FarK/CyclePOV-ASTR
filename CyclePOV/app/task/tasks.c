#define   TASKS_C
#include  <tasks.h>

CPU_CHAR FrameMemPartitionStorage[TASK_COM_NUM_FRAMES][TASK_COM_FRAME_LEN];

void AppObjCreate (void)
{
	OS_ERR err;

	//Memory partition for frame data
	OSMemCreate(&FrameMemPartition,
				(CPU_CHAR*) "Frame Memory Partition",
				(void*)&FrameMemPartitionStorage[0][0],
				(OS_MEM_QTY )TASK_COM_FRAME_LEN,
				(OS_MEM_SIZE)TASK_COM_FRAME_LEN,
				(OS_ERR *)&err
	);

	if(err != OS_ERR_NONE)
	{
		//TODO
	}
}

void AppTaskCreate (void)
{
	OS_ERR errorLeds;
	OS_ERR errorCommunication;

	//LEDs TASK
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
				 (OS_ERR     *)&errorLeds);

	//COMMUNICATION TASK
	OSTaskCreate((OS_TCB     *)&TCommunicationTCB,
				 (CPU_CHAR   *)"COMMUNICATION",
				 (OS_TASK_PTR )TCommunication,
				 (void       *)0,
				 (OS_PRIO     )TASK_COMMUNICATION_PRIORITY,
				 (CPU_STK    *)&TCommunicationStk[0],
				 (CPU_STK_SIZE)TASK_COMMUNICATION_STK_SIZE / 10,
				 (CPU_STK_SIZE)TASK_COMMUNICATION_STK_SIZE,
				 (OS_MSG_QTY  )TASK_COM_NUM_FRAMES,
				 (OS_TICK     )0,
				 (void       *)0,
				 (OS_OPT      )(OS_OPT_TASK_STK_CHK | OS_OPT_TASK_STK_CLR),
				 (OS_ERR     *)&errorCommunication);


	if(errorLeds != OS_ERR_NONE || errorCommunication != OS_ERR_NONE)
	{
		//TODO
	}
}
