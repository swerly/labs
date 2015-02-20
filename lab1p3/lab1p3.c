// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include "p24fj64ga002.h"
#include "leds.h"
#include "lcd.h"
#include "timer.h"
#include <stdio.h>


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )


// ******************************************************************************************* //

#define RUN_STOP PORTBbits.RB2 //these weren't working when I had them in leds.h
#define RESET PORTBbits.RB5    //so now they're here

typedef enum stateTypeEnum{
    run,
    stop,
    debouncePress,
    debounceRelease,
    reset
} stateType;

volatile stateType curState, nextState;
volatile int DEBOUNCE_DELAY_US = 5000;
volatile int min = 0, sec = 0, hs = 0, rsP = 0, ssP = 0, ms=0, i;
volatile char* time;


int main(void)
{
    initLEDs();
    initSW1();
    initSW2();
    initLCD();
    initTMR2();

    curState = stop;

    while(1){
        printTime(getTimeString(min, sec, hs));
        switch (curState){
            case run:
                STOP = OFF;
                RUN = ON;
                printRunning();
                break;

            case stop:
                RUN = OFF;
                STOP = ON;
                printStopped();
                break;

            case debouncePress:
                delayUs(DEBOUNCE_DELAY_US);
                curState = nextState;
                break;

            case debounceRelease:
                delayUs(DEBOUNCE_DELAY_US);
                curState = nextState;
                break;

            case reset:
                min = 0;
                sec = 0;
                hs = 0;
                curState = stop;
        }
    }
    
    return 0;
}

void _ISR _T2Interrupt(){
    IFS0bits.T2IF = 0;//put down flag

    if (curState == run){//if we are in the run state
        hs+=1;

        if (hs > 99){ //need to increment seconds
            hs = 0; //reset ms
            sec+=1;

            if (sec > 59){ //need to increment minutes
                sec = 0; //reset seconds
                min +=1;
            }
        }
    }
}

void _ISR _CNInterrupt(){
    IFS1bits.CNIF = 0;//put flag down
    
    if (RESET == PRESSED){
        ///so we know what state we were in after debounce
            //don't want to switch states until button release
           if(curState != debouncePress && curState != debounceRelease)
               nextState = curState;
            //go to debounce
            curState = debouncePress;
            rsP = 1;//reset pressed
    }
    else if(RESET == RELEASED && rsP == 1){//rsp so it doesnt enter when RUN_STOP is pressed/released
        if (curState == stop){
            nextState = reset;
            curState = debounceRelease;
        }
        rsP = 0;

    }

    else if (RUN_STOP == PRESSED){
        //so we know what state we were in after debounce
        //don't want to switch states until button release
       if(curState != debouncePress && curState != debounceRelease)
           nextState = curState;
        //go to debounce
        curState = debouncePress;

        ssP = 1;
    }
    else if (RUN_STOP == RELEASED && ssP == 1){
        if (curState == run){
                nextState = stop;
        }
        else if (curState == stop) nextState = run;
         //goto debounce
        curState = debounceRelease;
        ssP=0;
    }
}

