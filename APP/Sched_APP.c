/*
 * Sched_APP.c
 *
 *  Created on: Jun 15, 2023
 *      Author: Muham
 */

/************************************************ Library include *******************************************************************/
#include "../Common/STD_TYPES.h"
/************************************************ Lower layer include **************************************************************/
#include "../MCAL/RCC/RCC_interface.h"
#include "../HAL/LED/LED.h"
#include "../scheduler/sched.h"
/***********************************************************************************************************************************/

/*Static functions to execute every period */
static void led_1_Blink();
static void led_2_Blink();
static void led_3_Blink();

/* define runnables for application */
const runnable_t app1Runnable = {
    .name="App1 Runnable"
    ,.periodMs= 5000
    ,.priority=0
    ,.runnable=led_1_Blink
};
const runnable_t app2Runnable = {
    .name="App2 Runnable"
    ,.periodMs= 10000
    ,.priority=1
    ,.runnable=led_2_Blink
};
const runnable_t app3Runnable = {
    .name="App3 Runnable"
    ,.periodMs= 15000
    ,.priority=2
    ,.runnable=led_3_Blink
};

int main()
{
	MRCC_voidSetCLKSatus(CLK_HSI, STATUS_ENABLE);
	if (MRCC_uint8CheckClkSourceReady(CLK_RDY_HSI) == CLK_SOURCE_READY)
		MRCC_voidSetClkSource(sys_clk_HSI);
	MRCC_voidSetPeripheralStaus(Bus_AHB1, AHB1_GPIOA, STATUS_ENABLE);
	LED_Init();

    /*register application runnables */
    sched_registerRunnable(&app1Runnable);
    sched_registerRunnable(&app2Runnable);
    sched_registerRunnable(&app3Runnable);

    /*scheduler init*/
    sched_init();
    /*scheduler start*/
    sched_start();

}
void led_1_Blink()
{
	/* toggle every 1 s */
	LED_ToggleLED(led_ti_left);
}
void led_2_Blink()
{
	/* toggle every 2s */
	LED_ToggleLED(led_ti_right);
}
void led_3_Blink()
{
	/* toggle every 2s */
	LED_ToggleLED(led_alarm);
}
