/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"

#define FCY 14745600
#define oneUS 5 //time for one microsecond using ps of 8

//Uses timer 3
void delayUs(unsigned int delay){

    //reset timer to 0 just in case
    TMR2 = 0;

    //set pr2
    PR2 = delay*oneUS;
    T2CONbits.TCKPS = 0b01; //prescalar 8
    IFS0bits.T2IF = 0; //put down interrupt flag
    T2CONbits.TON = 1; //turn the timer on

    while(!IFS0bits.T2IF);

    IFS0bits.T2IF = 0;
    T3CONbits.TON = 0;

}