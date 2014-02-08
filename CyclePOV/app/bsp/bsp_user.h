#ifndef  BSP_USER_H
#define  BSP_USER_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   BSP_USER_C
#define  BSP_USER_EXT
#else
#define  BSP_USER_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <bsp_sensor.h>
#include <bsp_timer.h>
#include <bsp_leds.h>

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

void		BSP_User_Init					  (void);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
