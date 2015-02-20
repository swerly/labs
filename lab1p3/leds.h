/* 
* File:   leds.h
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#ifndef LEDS_H
#define	LEDS_H

#define STOP LATAbits.LATA0 //defines output for stop led
#define RUN LATAbits.LATA1  //defines output for run led
#define RESET PORTBbits.RB5      //used to read value of reset switch
#define START_STOP PORTBbits.RB2 //used to read value of start/stop switch
#define OFF 1 //led off
#define ON 0  //led on
#define PRESSED 0  //switch pressed
#define RELEASED 1 //switch released

void initLEDs();
void initSW1();
void initSW2();

#endif	/* LEDS_H */

