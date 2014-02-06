#ifndef  BSP_LEDS_H
#define  BSP_LEDS_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_LEDS_C
#define  BSP_LEDS_EXT
#else
#define  BSP_LEDS_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <cpu.h>
#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_gpio.h>
#include <stm32f4xx_dma.h>
#include <stm32f4xx_spi.h>
#include <misc.h>

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define NUM_IMAGES			8
#define NUM_SPOKES			4
#define NUM_LEDS			3

#define RGB_BITS_PER_LED	24
#define BITS_PER_RGB_BIT	3

#define NUM_RGB_BITS		(RGB_BITS_PER_LED * NUM_LEDS)
#define NUM_BITS			(NUM_RGB_BITS * BITS_PER_RGB_BIT)
#define LED_BUFFER_SIZE		((NUM_BITS / 8) + 3)

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

#define CLAMP(value, low, high) (((value)<(low))?(low):(((value)>(high))?(high):(value)))

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void		BSP_Leds_Init					();
void 		BSP_Leds_ClearBuffer			();
void 		BSP_Leds_SetBuffer				(CPU_INT32U num_spoke);
void 		BSP_Leds_DMAEnable				();
void		BSP_Leds_DMADisable				();

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
