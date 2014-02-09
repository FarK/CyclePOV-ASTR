#ifndef  BSP_SENSOR_H
#define  BSP_SENSOR_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_SENSOR_C
#define  BSP_SENSOR_EXT
#else
#define  BSP_SENSOR_EXT  extern
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

void		BSP_Sensor_Init					();
CPU_INT08U	BSP_Sensor_Event				();
CPU_INT32U	BSP_Sensor_Period				();

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
