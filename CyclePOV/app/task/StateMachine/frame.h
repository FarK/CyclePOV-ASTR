#ifndef H_FRAME
#define H_FRAME

#include <stdint.h>

#define STX 0x02
#define DLE 0x10
#define DATA_LENGTH 16	//Maximo tamaño teorico = 512

typedef struct
{
	uint8_t length;
	uint8_t ns;
	uint8_t t;
	uint8_t data[DATA_LENGTH];
	uint8_t crc;
} Frame;

#endif
