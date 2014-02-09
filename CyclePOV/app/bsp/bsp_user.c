#define   BSP_USER_C
#include  <bsp_user.h>

void BSP_User_Init(void)
{
	BSP_Sensor_Init();
	BSP_Timer_Init();
	BSP_Leds_Init();
	BSP_Button_Init();
}
