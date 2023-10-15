/*
 * app.c
 *
 *  Created on: Oct 15, 2023
 *      Author: omars
 */

#include "lcd.h"
#include "ultrasonic.h"
#include <avr/io.h> /*To enable I-bit*/

int main(void){
	uint16 distance;
	SREG|=(1<<7);
	LCD_init();
	Ultrasonic_init();
	LCD_displayString("Distance=    cm");
	while(1){
		distance=Ultrasonic_readDistance();
		LCD_moveCursor(0,10);
		LCD_intgerToString(distance);
		if(distance<100){
			LCD_displayCharacter(' ');
		}
	}
}
