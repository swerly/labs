/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define STOP LATAbits.LATA0
#define RUN LATAbits.LATA1
#define OFF 1
#define ON 0
#define PRESSED 0
#define RELEASED 1
#define RUN_STOP PORTBbits.RB2
#define RESET PORTBbits.RB5

void initLEDs();
void initSW1();
void initSW2();

#endif	/* LEDS_H */

