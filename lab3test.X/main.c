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

volatile int ad0val = 0,//holds the value read from adc1buf
             done = 0;
volatile float voltage;//holds the voltage

//don't need this yet
/*typedef enum stateTypeEnum{
    
} stateType;*/

int main(void){
    char v[10];

    initLCD();
    initADC();
    initLCDPWM();
    //initMotorOnePWM(); //turn these on to test output on oscope
    //initMotorTwoPWM();

    while(1){

        if(done){//dont think i need this if statement
            voltage = 3.3*((float)ad0val)/1023; //5 volts times the ratio
        }
        moveCursorLCD(0,1);
        sprintf(v, "%.3f V", voltage);
        printStringLCD(v);

    }
}

//will be called after 10 samples
void _ISR _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0; //put down flag

    ad0val = ADC1BUF0; //pull the value from the buffer
    done = 1; //dont think i need this
}