#ifndef  TASK_COMMUNICATION_H
#define  TASK_COMMUNICATION_H

/*
*********************************************************************************************************
*                                                 EXTERNS
*********************************************************************************************************
*/

#ifdef   TASK_COMMUNICATION_C
#define  TASK_COMMUNICATION_EXT
#else
#define  TASK_COMMUNICATION_EXT  extern
#endif


/*
*********************************************************************************************************
*                                              INCLUDE FILES
*********************************************************************************************************
*/

#include <os.h>
#include <bsp.h>
#include <tasks.h>

/*
*********************************************************************************************************
*                                               CONSTANTS
*********************************************************************************************************
*/

#define TASK_COMMUNICATION_PRIORITY	1
#define TASK_COMMUNICATION_STK_SIZE	512

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

TASK_COMMUNICATION_EXT	OS_TCB		TCommunicationTCB;
TASK_COMMUNICATION_EXT	CPU_STK		TCommunicationStk[TASK_COMMUNICATION_STK_SIZE];

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

TASK_COMMUNICATION_EXT	void		TCommunication		(void *p_arg);

/*
*********************************************************************************************************
*                                             MODULE END
*********************************************************************************************************
*/

#endif
