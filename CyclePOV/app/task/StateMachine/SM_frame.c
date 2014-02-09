#include <SM_frame.h>

void initFrameSM(FrameSM* frameSM){
	frameSM->state = SM_WAIT_STX;
	frameSM->frame = 0;
	frameSM->escapedByte = 0;
	frameSM->dataIndex = 0;
}

int fsm_newByte(uint8_t newByte, FrameSM* frameSM){
	int frameComplete = 0;

	/* Ejecutamos la máquina de estados solo si hay que reconocer el
	 * caracter actual.  Para cada estado, comprobamos si el caracter
	 * actual es el de comienzo de una nueva trama. O si el byte ha sido
	 * "escapado".
	 */
	if(frameSM->escapedByte || newByte != DLE){
	switch(frameSM->state){
			case SM_WAIT_STX:
				if(!frameSM->escapedByte && newByte == STX)
					frameSM->state = SM_LENGTH;
			break;

			case SM_LENGTH:
				if(frameSM->escapedByte || newByte != STX){
					if(newByte > 0)	frameSM->state = SM_NS_T;
					else 		frameSM->state = SM_ACK;
					
					frameSM->frame->length = newByte;
					frameSM->dataIndex = 0;
				}
				else
					frameSM->state = SM_LENGTH;
			break;

			case SM_NS_T:
				if(frameSM->escapedByte || newByte != STX){
					frameSM->frame->ns = newByte >> 1;
					frameSM->frame->t = newByte & 0x01;

					frameSM->state = SM_DATA;
				}
				else
					frameSM->state = SM_LENGTH;
			break;

			case SM_ACK:
				if(frameSM->escapedByte || newByte != STX){
					frameSM->frame->ns = newByte >> 1;
					frameSM->frame->t = newByte & 0x01;

					frameSM->state = SM_CRC;
				}
				else
					frameSM->state = SM_LENGTH;
			break;

			case SM_DATA:
				if(frameSM->escapedByte || newByte != STX){
					frameSM->frame->data[frameSM->dataIndex++] = newByte;

					if(frameSM->dataIndex >= frameSM->frame->length)
						frameSM->state = SM_CRC;
				}
				else
					frameSM->state = SM_LENGTH;
			break;

			case SM_CRC:
				if(frameSM->escapedByte || newByte != STX){
					frameSM->frame->crc = newByte;

					frameSM->state = SM_WAIT_STX;

					frameComplete = 1;
				}
				else
					frameSM->state = SM_LENGTH;
			break;
		}
	}

	//Actualizamos el flag de byte escapado.
	if(frameSM->escapedByte) frameSM->escapedByte = 0;
	else if(newByte == DLE) frameSM->escapedByte = 1;

	return frameComplete;
};
