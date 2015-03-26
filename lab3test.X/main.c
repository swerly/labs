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

typedef enum stateTypeEnum{
    voltageLCD,
    motor
} stateType;

volatile int ad0val = 0,//holds the value read from adc1buf
             done = 0,
             count = 0,
             dutyCycle = 50,
             dir = FORWARD;
volatile double voltage;//holds the voltage. use double b/c compiler sprintf hates floats
volatile stateType curState;



int main(void){
    char v[10];

    initLCD();
    initADC();
    initLCDPWM();
    initMotorOnePWM(); //TODO: take pictures of output on oscope
    initMotorTwoPWM();

    while(1){
        curState = voltageLCD;

        switch(curState){
            case voltageLCD:

                voltage = 3.3*((double)ad0val)/1023; //3.3 volts times the ratio
                moveCursorLCD(0,1);//move the cursor to center the text
                sprintf(v, "%.3f V", voltage); //make a new string out of the voltage float
                printStringLCD(v); //print the new string to the LCD
                break;

            case motor:
                if (dutyCycle < 100){//if we haven't reached maxed speed
                    dutyCycle += 25;//update the duty cycle by 25%
                    setDutyCycle(MOTOR_ONE, dutyCycle);
                    setDutyCycle(MOTOR_TWO, dutyCycle);
                }
                else if (dutyCycle == 100){ //if the duty cycle is already maxed
                    dutyCycle = 50;//change back to 50% (anything lower is crap)
                    setDutyCycle(MOTOR_ONE, dutyCycle);
                    setDutyCycle(MOTOR_TWO, dutyCycle);

                    if (dir == FORWARD){ // if we're currently going forward
                        setDirection(REVERSE);// start going reverse
                        dir = REVERSE;
                    }
                    else if (dir == REVERSE){ // if we're currently going in reverse
                        setDirection(FORWARD);// start going forward
                        dir = FORWARD;
                    }
                }

                curState = voltageLCD; //go back to printing the voltage after pwm change

                break;

        }
        if(done){//dont think i need this if statement
            
        }
        
        

    }
}

//will be called after 10 samples
void _ISR _ADC1Interrupt(void){
    IFS0bits.AD1IF = 0; //put down flag

    ad0val = ADC1BUF0; //pull the value from the buffer
}

void _ISR _T1Interrupt(void){
    //Put down the timer 1 flag first!
    IFS0bits.T1IF = 0;

    //timer will go off every second and we want to change duty cycle of motors
    //every two seconds, so increment count
    count++;
    
    //when we've reached 2 seconds we want to change the motor pwm
    if (count >= 2){
        curState = motor;
    }
    

    //increment timerX4 as long as the button is pressed

}