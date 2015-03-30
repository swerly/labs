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
             count = 0,
             dir = FORWARD;
volatile double voltage;//holds the voltage. use double b/c compiler sprintf hates floats
volatile float dutyCycle = 0,
               pwm = 50;


int main(void){
    char v[10], test[10];
    
    initLCD();
    initADC();
    initTimer5(); //enabling this breaks everything for some reason?
    initLCDPWM();
    initMotorOnePWM();
    initMotorTwoPWM();
    T3CONbits.TON = 1;//PUT THIS AFTER PWM INITS

    while(1){

        

        voltage = 3.3*((double)ad0val)/1023; //3.3 volts times the ratio
        moveCursorLCD(0,1);//move the cursor to center the text
        sprintf(v, "%.3f V", voltage); //make a new string out of the voltage float
        printStringLCD(v); //print the new string to the LCD


        //TESTING IF COUNTER IS WORKING
        sprintf(test, "%d", count);
        moveCursorLCD(1,0);
        printStringLCD(test);

        //IF COUNTER WORKS ENABLE THIS CODE
        /*
        if (count >=2){ //if we have reached 2s we want to change duty cycle
            if (pwm < 100){ //if we haven't reached max speed
                pwm += 25;  //increase speed
                setDutyCycle(BOTH,pwm);
            }
            else if (pwm >= 100){ //if we have reached max speed
                pwm = 50;// reset pwm to 50
                setDutyCycle(BOTH,pwm);

                //change directions
                if (dir = FORWARD) dir = REVERSE;
                else if (dir == REVERSE) dir = FORWARD;
                setDirection(BOTH, dir);
            }
         *
        count = 0; //reset count
        }
        */



        }
    
}

//will be called after 10 samples
void _ISR _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0; //put down flag

    ad0val = ADC1BUF0; //pull the value from the buffer
}

void _ISR _T5Interrupt(void){
    //Put down the timer 1 flag first!
    IFS1bits.T5IF = 0;

    //timer will go off every second and we want to change duty cycle of motors
    //every two seconds, so increment count
    count++;

}