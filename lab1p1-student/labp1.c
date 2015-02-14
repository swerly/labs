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

volatile stateType curState;
volatile int debounce = 5;

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

                break;
            case stop:
                break;
            case debouncePress:
                delayMs(5);
                break;
            case debounceRelease:
                delayMs(5);
                break;

        }

    }
    
    return 0;
}

void _ISR _CNInterrupt(void){
    //if our switch is pressed we need to debounce
    if ()

}