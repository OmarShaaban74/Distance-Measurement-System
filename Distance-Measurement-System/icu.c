/*
 * icu.c
 *
 *  Created on: Oct 11, 2023
 *      Author: omars
 */

#include <avr/io.h>
#include"icu.h"
#include <avr/interrupt.h>

static volatile void (*g_callBackPtr)(void) = NULL_PTR;

/*
 * Description:
 * 1-Setup pin6 at port_D as input
 * 2-Timer0 working at no-PWM MODE
 * 3-Configure the edge and the clock
 * 4-enable ICU interrupt
 */

void ICU_init(const ICU_ConfigType *Config_Ptr){
	DDRD&=~(1<<6);
	TCCR1A=(1<<FOC1A)|(1<<FOC1B);
	TCCR1B= (TCCR1B&(0xBF)) | (Config_Ptr->edge<<ICES1);
	TCCR1B= (TCCR1B&(0xF8)) | (Config_Ptr->clock);
	ICR1=0;
	TCNT1=0;
	TIMSK|=(1<<TICIE1);

}
/*Description:
 *Interrupt service routine for timer0 calls the call-back function
 **/
ISR(TIMER1_CAPT_vect)
{
	if(g_callBackPtr != NULL_PTR)
	{
		/* Call the Call Back function in the application after the edge is detected */
		(*g_callBackPtr)();
	}
}
/*Description:
 * Choose the call-back function
 * */
void ICU_setCallBack(void(*a_ptr)(void))
{
	/* Save the address of the Call back function in a global variable */
	g_callBackPtr = a_ptr;
}

/*Description:
 * Choose the edge that will be triggered
 * */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType)
{
	TCCR1B= (TCCR1B&(0xBF)) | (a_edgeType<<ICES1);
}

/*Description:
 * Return the time;
 * */
uint16 ICU_getInputCaptureValue(void)
{
	return ICR1;
}
/*Description:
 * Clear the time
 * */
void ICU_clearTimerValue(void)
{
	TCNT1 = 0;
}

void ICU_deInit(void)
{
	/* Clear All Timer1/ICU Registers */
	TCCR1A = 0;
	TCCR1B = 0;
	TCNT1 = 0;
	ICR1 = 0;

	/* Disable the Input Capture interrupt */
	TIMSK &= ~(1<<TICIE1);

	/* Reset the global pointer value */
	g_callBackPtr = NULL_PTR;
}

