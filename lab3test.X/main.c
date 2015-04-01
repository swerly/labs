#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"
#include "adc.h"
#include "pwm.h"
#include <stdio.h>

#define DEBOUNCE_DELAY_US 5000


_CONFIG1( JTAGEN_OFF & GCP_OFF & GWRP_OFF & BKBUG_ON & COE_OFF & ICS_PGx1 &
          FWDTEN_OFF & WINDIS_OFF & FWPSA_PR128 & WDTPS_PS32768 )

_CONFIG2( IESO_OFF & SOSCSEL_SOSC & WUTSEL_LEG & FNOSC_PRIPLL & FCKSM_CSDCMD & OSCIOFNC_OFF &
          IOL1WAY_OFF & I2C1SEL_PRI & POSCMOD_XT )

volatile int adcVal = 0,//holds the value read from adc1buf
             count = 0,
             done = 0,
             dir = FORWARD,
             dutyCycle = 0;
volatile double voltage;//holds the voltage. use double b/c compiler sprintf hates floats


int main(void){
    char v[10];
    
    initLCD();
    //moveCursorLCD(0,0);
    //printStringLCD("HELLO!!!");
    initADC();
    initMotorOnePWM(); //also enables T3 for pwm
    initMotorTwoPWM();
    initTimerPWM();

    
    while(1){

        
        if(done){
            voltage = 3.3*((double)adcVal)/1023; //3.3 volts times the ratio
            moveCursorLCD(0,1);//move the cursor to center the text
            sprintf(v, "%.3f V", voltage); //make a new string out of the voltage double
            printStringLCD(v);
            
            dutyCycle = (unsigned int) ((voltage/3.3)*100);//convert the found voltage to a percent 0-100
            setDutyCycle(BOTH, dutyCycle);
            
            done = 0;
            AD1CON1bits.ADON = 1; //turn the adc back on
        }
        



        }
    return 0;
}


void _ISR _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0;

    int i = 0;
    unsigned int *adcPtr;
    adcVal = 0;
    adcPtr = (unsigned int *) (&ADC1BUF0);

    for(i = 0; i < 16; i++){
        adcVal = adcVal + *adcPtr/16;
        adcPtr++;
    }

    done = 1;
}
