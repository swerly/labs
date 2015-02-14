// ******************************************************************************************* //
//
// File:         lab1p1.c
// Date:         
// Authors:      
//
// Description: Part 1 for lab 1
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "leds.h"
#include "timer.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

// ******************************************************************************************* //
typedef enum stateTypeEnum{
    run,
    stop,
    debouncePress,
    debounceRelease
} stateType;

volatile stateType curState, nextState;
volatile int DEBOUNCE_DELAY_US = 5000; //5000us = 5ms

int main(void)
{
    initLEDs();
    initSW2();
    curState = run;

    while(1)
    {
        switch(curState){
            case run:
                STOP = OFF;
                RUN = ON;
                break;
            case stop:
                //turn off run led and turn on stop led
                RUN = OFF;
                STOP = ON;
                break;
            case debouncePress:
                //debounce 5ms then go to next state so debounce only occurs
                //per button press
                delayMs(DEBOUNCE_DELAY_US);
                curState = nextState;
                break;
            case debounceRelease:
                //debounce 5ms then go to next state so debounce only occurs
                //per button release
                delayMs(DEBOUNCE_DELAY_US);
                curState = nextState;
                break;

        }

    }
    
    return 0;
}

void _ISR _CNInterrupt(void){
    //if our switch is pressed we need to debounce
    if (PORTBbits.RB2 == PRESSED){
        //so we know what state we were in after debounce
        //don't want to switch states until button release
        nextState = curState;
        //go to debounce
        curState = debouncePress;
    }
    else {
        if (curState == run) nextState = stop;
        else if (curState == stop) nextState = run;

        //goto debounce
        curState = debounceRelease;
    }

}