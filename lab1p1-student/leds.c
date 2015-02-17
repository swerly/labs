/*
* File:   leds.c
* Author: 
*
* Created on December 27, 2014, 1:31 PM
*/

#include "p24fj64ga002.h"
#include "leds.h"

void initLEDs(){
    //TODO: do some of this stuff with bits yo

    //turn on odc for each input pin
    ODCAbits.ODA0 = 1;
    ODCAbits.ODA1 = 1;
    //set both pins as outputs
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 0;
    //turn off both of the leds
    STOP = OFF;
    RUN = OFF;

}
/*
void initSW1(){
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 0; //set overall CN interrupt flag to 0
    IEC1bits.CNIE = 1; //enable interrupts system wide
    CNEN2bits.CN27IE = 1;//enable CN interrupt for sw1 (cn27 from datasheet)
}*/


void initSW2(){
    AD1PCFGbits.PCFG4 = 1;//set analot input to be digital
    //pcfg4 refers to an4 (pin6)
    CNPU1bits.CN6PUE = 1; //enable the internal pull up resistor
    //cn6pue refers to using the pu for cn pin 6
    TRISBbits.TRISB2 = 1;//set rb 2 as an input (rb2 = pin6 = io5)
    IFS1bits.CNIF = 0;//put down cni flag
    IEC1bits.CNIE = 1;//enable global cn interrupt flag
    CNEN1bits.CN6IE = 1;//enable cn for pin 6 (io5)

}