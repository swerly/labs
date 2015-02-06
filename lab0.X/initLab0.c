/*
* File:   initLab0.c
* Author: Seth Werly
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "initLab0.h"

#define FCY 14745600.0
#define TIME_DELAY 1

void initLEDs(){
    //initialize leds (pins rb12-15
    TRISBbits.TRISB12 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB15 = 0;

    //make sure leds are turned off
    LED4 = OFF;
    LED5 = OFF;
    LED6 = OFF;
    LED7 = OFF;


}

void turnOnLED(int led){
    if (led == 4){
        LED4 = ON;
        LED5 = OFF;
        LED6 = OFF;
        LED7 = OFF;
    }
    else if (led == 5){
        LED4 = OFF;
        LED5 = ON;
        LED6 = OFF;
        LED7 = OFF;
    }
    else if (led == 6){
        LED4 = OFF;
        LED5 = OFF;
        LED6 = ON;
        LED7 = OFF;
    }
    else if (led == 7){
        LED4 = OFF;
        LED5 = OFF;
        LED6 = OFF;
        LED7 = ON;
    }
}

void initSW1(){
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0; //set overall CN interrupt flag to 0
    IEC1bits.CNIE = 1; //enable interrupts system wide
    CNEN2bits.CN27IE = 1;//enable CN interrupt for sw1 (cn27 from datasheet)
}


void initTimer1(){
    //this timer will go off every .5s. So we need to run through 4 of these
    //to equal the 2s timer we want
    unsigned int prVal = ((FCY*TIME_DELAY)/256) - 1;
    PR1 = prVal;

    T1CONbits.TCKPS = 0b11; //prescalar 256
    IEC0bits.T1IE = 1; //timer 1 interrupt enable
    IFS0bits.T1IF = 0; //timer 1 interrupt flag put down
    T1CONbits.TON = 1; //timer 1 on

}