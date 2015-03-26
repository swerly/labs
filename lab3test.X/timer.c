/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"
#include <stdio.h>

///TIMER 1 USED IN DELAYUS FUNCTION
///TIMER 2 USED FOR CONTROLLING MOTORS
///TIMER 3 USED FOR PWM SIGNALS



#define FCY 14745600
#define oneUS 14//time for one microsecond using ps of 8
#define TIME_DELAY 1

void initTimer2(){
    unsigned int prVal = ((FCY*TIME_DELAY)/256) - 1;
    PR1 = prVal;

    T2CONbits.TCKPS = 0b11; //prescalar 256
    IEC0bits.T2IE = 1; //timer 2 interrupt enable
    IFS0bits.T2IF = 0; //timer 2 interrupt flag put down
    T2CONbits.TON = 1; //timer 2 on

}

//Uses timer 2
void delayUs(unsigned int delay){
    //MAX DELAY: ~65500us = 65.5ms
    //reset timer to 0 just in case
    TMR1 = 0;

    //set pr1
    PR1 = delay*oneUS;
    T1CONbits.TCKPS = 0b00; //prescalar 1
    IFS0bits.T1IF = 0; //put down interrupt flag
    T1CONbits.TON = 1; //turn the timer on

    while(IFS0bits.T1IF == 0){
        if (TMR1 >= PR1) break;
    }//wait until the timer flag goes up

    IFS0bits.T1IF = 0; // Put the flag down afterwards.
    T1CONbits.TON = 0; // Turn the timer off so it does not keep counting.
}

