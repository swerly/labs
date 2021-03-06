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
///TIMER 5 USED FOR CONTROLLING MOTORS
///TIMER 3 USED FOR PWM SIGNALS



#define FCY 14745600
#define oneUS 14//time for one microsecond using ps of 8
#define TIME_DELAY 1
#define PRVAL 56

void initTimerPWM(){
    T3CONbits.TCKPS = 256;
    TMR3 = 0;
    PR3 = PRVAL;
    T3CONbits.TON = 1;
}

void initTimer5(){
    //this timer will go off every 1s
    unsigned int prVal = ((FCY*TIME_DELAY)/256) - 1;
    PR5 = prVal;

    T5CONbits.TCKPS = 0b11; //prescalar 256
    IEC1bits.T5IE = 1; //timer 5 interrupt enable
    IFS1bits.T5IF = 0; //timer 5 interrupt flag put down
    T5CONbits.TON = 1; //timer 5 on

}

//Uses timer 1
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

