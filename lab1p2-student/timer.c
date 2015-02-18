/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 14745600
#define oneUS 14//time for one microsecond using ps of 8

//Uses timer 2
void delayUs(unsigned int delay){
    //MAX DELAY: ~65500us = 65.5ms

    //reset timer to 0 just in case
    TMR2 = 0;

    //set pr2
    PR2 = delay*oneUS;
    T2CONbits.TCKPS = 0b00; //prescalar 8
    IFS0bits.T2IF = 0; //put down interrupt flag
    T2CONbits.TON = 1; //turn the timer on

    while(IFS0bits.T2IF == 0);//wait until the timer flag goes up

    IFS0bits.T2IF = 0; // Put the flag down afterwards.
    T2CONbits.TON = 0; // Turn the timer off so it does not keep counting.
}