// ******************************************************************************************* //
//
// File:         lab0.c
// Date:         Febrary 1, 2015
// Authors:      Seth Werly
//
// Description:  Lab 0 assignment for ECE 372 Spring 2015.
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "initLab0.h"
#include <stdio.h>

// ******************************************************************************************* //
// Configuration bits for CONFIG1 settings.
//
// These settings are appropriate for debugging the PIC microcontroller. If you need to
// program the PIC for standalone operation, change the COE_ON option to COE_OFF.

_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF &
          BKBUG_ON & COE_ON & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

typedef enum stateTypeEnum{
    led4,
    led5,
    led6,
    led7
} stateType;

volatile stateType curState; //to keep track of the current state
volatile int c2 = 0; //to keep track of seconds elapsed

int main(void)
{

    //initialize and set the things we need
    initLEDs();
    initTimer1();
    initSW1();
    curState = led4;
    
    while(1)
    {
        switch(curState){
            case led4:
                turnOnLED(4);
                break;
            case led5:
                turnOnLED(5);
                break;
            case led6:
                turnOnLED(6);
                break;
            case led7:
                turnOnLED(7);
                break;
        }
    }
    return 0;
}

void _ISR _CNInterrupt(void){
    IFS1bits.CNIF = 0; //put down flag
    
    //if the button was released and has been held for > 2s 
    if (PORTBbits.RB5 == 1 && c2 >= 2){
        if (curState == led4) curState = led7;
        else if (curState == led5) curState = led4;
        else if (curState == led6) curState = led5;
        else if (curState == led7) curState = led6;

        c2 = 0; //reset the counter
    }
    //if the button was released and c2 hasnt reached 2 go to the next led
    else if(PORTBbits.RB5 == 1 && c2 < 2){
        if (curState == led4) curState = led5;
        else if (curState == led5) curState = led6;
        else if (curState == led6) curState = led7;
        else if (curState == led7) curState = led4;

        c2 = 0; //reset the counter
    }

}


void _ISR _T1Interrupt(void){
    //Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;

    //increment timerX4 as long as the button is pressed
    if(PORTBbits.RB5 == 0)
        c2++;
    else
        c2=0;

}