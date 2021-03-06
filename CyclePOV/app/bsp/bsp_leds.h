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

#define NUM_ANIMATIONS 		20
#define NUM_IMAGES			88

#define NUM_SPOKES			128
#define NUM_LEDS			28
#define NUM_GROUPS			2

#define RGB_BITS_PER_LED	24
#define BITS_PER_RGB_BIT	3

#define NUM_RGB_BITS		(RGB_BITS_PER_LED * NUM_LEDS)
#define NUM_BITS			(NUM_RGB_BITS * BITS_PER_RGB_BIT)
#define LED_BUFFER_SIZE		((NUM_BITS / 8) + 3)

#define MIN_WAIT_TIME_US	((int)(1.2 * NUM_RGB_BITS) + 51)

#define PROPORTION			1.2

#define NUM_MODES			2

/*
*********************************************************************************************************
*                                               DATA TYPES
*********************************************************************************************************
*/

typedef enum mode
{
	MODE_SEQUENTIAL		= 0u,
	MODE_STATIC			= 1u,
} MODE;

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

#define US_TO_TICKS(us) (us * 80)

/*
*********************************************************************************************************
*                                           FUNCTION PROTOTYPES
*********************************************************************************************************
*/

void		BSP_Leds_Init					();

void 		BSP_Leds_ClearBuffers			();

void		BSP_Leds_NextImage				();
void		BSP_Leds_ResetSpokes			();
CPU_INT08U 	BSP_Leds_NextSpoke				();

void 		BSP_Leds_DMAEnable				();
void		BSP_Leds_DMA1Disable			();
void		BSP_Leds_DMA2Disable			();

void		BSP_Leds_Switch					();

void 		BSP_Leds_SetMode				(MODE mode, CPU_INT32U animation);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
