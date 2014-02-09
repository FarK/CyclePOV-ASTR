#ifndef H_SM_FRAME
#define H_SM_FRAME

#include <stdint.h>
#include <frame.h>

typedef enum
{
	SM_WAIT_STX,
	SM_LENGTH,
	SM_NS_T,
	SM_ACK,
	SM_DATA,
	SM_CRC
} FrameState;

typedef struct
{
	FrameState state;
	Frame* frame;
	int escapedByte;
	uint8_t dataIndex;
} FrameSM;

void 	initFrameSM		(FrameSM* frameSM);
int 	fsm_newByte		(uint8_t newByte, FrameSM* frameSM);

#endif
