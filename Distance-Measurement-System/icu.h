/*
 * icu.h
 *
 *  Created on: Oct 11, 2023
 *      Author: omars
 */

#ifndef ICU_H_
#define ICU_H_
#include "Standerd_Types_OS.h"

/***********************************Types declaration******************************/

/*Edge state*/
typedef enum{
	FALLING,RAISING
}ICU_EdgeType;

/*Clock value*/
typedef enum{
	NO_CLOCK,F_CPU_CLOCK,F_CPU_8,F_CPU_64,F_CPU_256,F_CPU_1024
}ICU_ClockType;

/*Structure that choose settings of ICU by passing it to ICU_init function */
typedef struct
{
	ICU_ClockType clock;
	ICU_EdgeType edge;
}ICU_ConfigType;

/***********************************Functions Prototype******************************/

/*
 * Description:
 * 1-Setup pin6 at port_D as input
 * 2-Timer0 working at no-PWM MODE
 * 3-Configure the edge and the clock
 * 4-enable ICU interrupt
 */
void ICU_init(const ICU_ConfigType *Config_Ptr);

/*Description:
 * Choose the call-back function
 * */
void ICU_setCallBack(void(*a_ptr)(void));

/*Description:
 * Choose the edge that will be triggered
 * */
void ICU_setEdgeDetectionType(const ICU_EdgeType a_edgeType);

/*Description:
 * Return the time;
 * */
uint16 ICU_getInputCaptureValue(void);

/*Description:
 * Clear the time
 * */
void ICU_clearTimerValue(void);

/*Description:
 *Clear All Timer1/ICU Registers
 *Disable the Input Capture interrupt
 *Disable Reset the global pointer value
 * */
void ICU_deInit(void);

#endif /* ICU_H_ */
