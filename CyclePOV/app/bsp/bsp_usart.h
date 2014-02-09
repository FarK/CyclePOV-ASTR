#ifndef  BSP_USART_H
#define  BSP_USART_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_USART_C
#define  BSP_USART_EXT
#else
#define  BSP_USART_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_spi.h>
#include <stm32f4xx_usart.h>
#include <misc.h>

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

//Tamaños máximos de la parte entera y la parte decimal
//a la hora de imprimir un float. ¡No pueden ser mayores que 10!
#define USART_NINTEGERS 10
#define USART_NDECIMALS 1e3

//Usart configuration parameters
#define USART_BAUD_RATE		2400
#define USART_WORD_LENGTH	USART_WordLength_8b
#define USART_STOP_BIT		USART_StopBits_2
#define USART_PARITY		USART_Parity_No
#define USART_FLOW_CONTROL	USART_HardwareFlowControl_None
//#define USART_MODE			USART_Mode_Rx | USART_Mode_Tx
#define USART_MODE			USART_Mode_Rx

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            GLOBAL VARIABLES
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                                 MACROS
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void		BSP_USART_Init				();

int			BSP_USART_Is_Tx_ISR			();
int			BSP_USART_Is_Rx_ISR			();
void		BSP_USART_Tx				();
uint8_t		BSP_USART_Rx				();
/*
int			BSP_USART_Send				(uint8_t* buffer, int length);
int			BSP_USART_Receive			(uint8_t* buffer, int length);

void		BSP_USART_SendAll			(uint8_t* buffer, int length);
void		BSP_USART_ReceiveAll		(uint8_t* buffer, int length);

void		BSP_USART_Print				(uint8_t* string);
void		BSP_USART_PrintLine			(uint8_t* string);
void		BSP_USART_PrintChar			(uint8_t character);
void		BSP_USART_PrintInt			(int32_t number);
void		BSP_USART_PrintFloat		(double number);
*/

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
