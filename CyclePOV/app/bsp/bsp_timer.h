#ifndef  BSP_TIMER_H
#define  BSP_TIMER_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_TIMER_C
#define  BSP_TIMER_EXT
#else
#define  BSP_TIMER_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <stm32f4xx.h>
#include <stm32f4xx_rcc.h>
#include <stm32f4xx_tim.h>

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

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

void		BSP_Timer_Init					();
void		BSP_Timer_SetPeriod				(uint32_t period);
void		BSP_Timer_Cmd				(FunctionalState state);
void		BSP_Timer_ClearIT				();

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
