#define TASK_COMMUNICATION_C
#include <task_communication.h>
#include <bsp_usart.h>
#include <frame.h>
#include <SM_frame.h>
#include <crc8.h>

FrameSM frameSM;

void ISR_USART(void)
{
	OS_ERR err;

	/*
	if(BSP_USART_Is_Tx_ISR())
			BSP_USART_Tx();
	*/

	if(BSP_USART_Is_Rx_ISR())
	{
		//Allocate memory for frame
		if(!frameSM.frame)
		{
			frameSM.frame = (Frame*)OSMemGet(&FrameMemPartition, &err);
		}

		//Process byte
		if(fsm_newByte(BSP_USART_Rx(), &frameSM))
		{
			//Send a message with the recognized frame
			OSTaskQPost(&TCommunicationTCB, (void *)frameSM.frame, sizeof(Frame), OS_OPT_POST_FIFO, &err);

			if(err != OS_ERR_NONE)
			{
				//TODO
			}

			frameSM.frame = 0;
		}
	}
}

void TCommunication(void *p_arg)
{
	OS_ERR err;
	Frame* frame;

	//Initialize the state machine for frame sync
	initFrameSM(&frameSM);

	//Configure USART and enable interruption
	BSP_USART_Init();
	BSP_IntVectSet(BSP_INT_ID_USART3, ISR_USART);

	//Wait for the next frame
	OS_MSG_SIZE size;

	while(DEF_ON)
	{
		//Get a frame
		frame = (Frame*)(OSTaskQPend(0, OS_OPT_PEND_BLOCKING, &size, 0, &err));

		//Process the frame
		if((Crc8(frame, sizeof(Frame) - 1) == frame->crc) && (frame->length == 2))
		{
			BSP_Leds_SetMode((MODE)frame->data[0], frame->data[1]);
		}

		//Free frame memory
		OSMemPut((OS_MEM *) &FrameMemPartition,
				 (void *  ) frame,
				 (OS_ERR *) &err);

		if(err != OS_ERR_NONE)
		{
			//TODO
		}
	}
}
