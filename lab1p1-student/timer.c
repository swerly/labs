/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 14745600
#define oneMS 57

//Uses timer 2
void delayMs(unsigned int delay){
    //reset timer to 0 just in case
    TMR2 = 0;

    //set pr2
    PR2 = delay*oneMS;
    T2CONbits.TCKPS = 0b11;
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 1;

    //wait until the flag goes up
    while(IFS0bits.T2IF == 0);

    IFS0bits.T2IF = 0; // Put the flag down afterwards.
    T2CONbits.TON = 0; // Turn the timer off so it does not keep counting.

}