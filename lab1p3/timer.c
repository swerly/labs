/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include "p24fj64ga002.h"
#include "timer.h"
#include <stdio.h>

#define FCY 14745600
#define DELAY_TEN_MS 575 //ten ms
#define oneUS 14//time for one microsecond using ps of 8

void initTMR3(){
    PR3 = DELAY_TEN_MS;

    T3CONbits.TCKPS = 0b11; //prescalar 256
    IEC0bits.T3IE = 1; //timer 1 interrupt enable
    IFS0bits.T3IF = 0; //timer 1 interrupt flag put down
    T3CONbits.TON = 1; //timer 1 on
}

//Uses timer 2
void delayUs(unsigned int delay){
    //MAX DELAY: ~65500us = 65.5ms

    //reset timer to 0 just in case
    TMR1 = 0;

    //set pr2
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

char* getTimeString(int min, int sec, int ms){
    static char time[8];

    sprintf(time, "%02d:%02d:%02d", min, sec, ms);

    return time;
}