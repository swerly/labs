#include "p24FJ64GA002.h"
#include "pwm.h"
#include "timer.h"
#include "lcd.h"

#define PRVAL 56

//initiates PWM to control the LCD contrast
void initLCDPWM(){
    T3CONbits.TCKPS = 256;
    TMR3 = 0;
    PR3 = PRVAL;

    TRISBbits.TRISB11 = OUTPUT;
    OC1CONbits.OCTSEL = 1; //use TMR3
    OC1CONbits.OCM = 6; //set oc to pwm
    RPOR5bits.RP11R = 18; //map OC1 to pin22 (rp11)

    OC1R = 0; //sets to the beginning of the period
    OC1RS = 10; //~.9 volts give the best display contrast
    
}

//sets motor one to be going forward initially
void initMotorOnePWM(){
    OC2CONbits.OCTSEL = 1; //use TMR3
    OC2CONbits.OCM = 6; //set oc to pwm
    RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

    TRISBbits.TRISB2 = OUTPUT;
    TRISBbits.TRISB3 = OUTPUT;
    ODCBbits.ODB3 = 1; //opposite side of the motor to odc

    OC2R = 0; //sets to the beginning of the period
    OC2RS = 0; //will change this later
}

//sets motor two to be going forward initially
void initMotorTwoPWM(){
    OC3CONbits.OCTSEL = 1; //use TMR3
    OC3CONbits.OCM = 6; //set oc to pwm
    RPOR4bits.RP8R = 20; //map OC3 to pin 17 (RP8)

    TRISBbits.TRISB8 = OUTPUT;
    TRISBbits.TRISB9 = OUTPUT;
    ODCBbits.ODB9 = 1;

    OC3R = 0; //sets to the beginning of the period
    OC3RS = 0; //will change this later
}

void setDutyCycle(int motor, float percent){
    if (motor == 1){
        OC2RS = (unsigned int)((percent/100)*PRVAL);
    }
    else if (motor == 2){
        OC3RS = (unsigned int)((percent/100)*PRVAL);
    }
}

void setDirection(int motor, int dir){
    //TODO: figure out why it's not switching from reverse to forward

    if (dir == FORWARD){

        if (motor == MOTOR_ONE){
            RPOR1bits.RP3R = 0; //map NOTHING to pin 7 (RP3)
            ODCBbits.ODB3 = 1; //opposite terminal of the motor to odc
            ODCBbits.ODB2 = 0; //turn off odc for pin 6 (RP2)
            RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)
        }

        if (motor == MOTOR_TWO){
            RPOR4bits.RP9R = 0; //map NOTHING to pin 18 (RP9)
            ODCBbits.ODB9 = 1;
            ODCBbits.ODB8 = 0;
            RPOR4bits.RP8R = 20;
        }
    }
    else if (dir == REVERSE){

        if (motor == MOTOR_ONE){
            RPOR1bits.RP2R = 0; //map NOTHING to pin 6 (RP2)
            ODCBbits.ODB2 = 1; //opposite terminal of the motor to odc
            ODCBbits.ODB3 = 0; //turn off odc for pin 7 (RP3)
            RPOR1bits.RP3R = 19; //map OC2 to pin 7 (RP3)
        }

        if (motor == MOTOR_TWO){
            RPOR4bits.RP8R = 0;//map NOTHING to pin 17 (RP8)
            ODCBbits.ODB8 = 1; //turn on odc for pin 17
            ODCBbits.ODB9 = 0; //turn off odc for pin 18
            RPOR4bits.RP9R = 20; //map OC3 to pin 18 (RP9)
        }
    }
    delayUs(5); //delay so pins have time to change
}

void testPWM(){
    int i = 0;
    setDirection(MOTOR_ONE, FORWARD);
    setDirection(MOTOR_TWO, FORWARD);
    setDutyCycle(MOTOR_ONE, 50);
    setDutyCycle(MOTOR_TWO, 50);
    for(i = 0; i<1000; i++) delayUs(2000);
    setDutyCycle(MOTOR_ONE, 75);
    setDutyCycle(MOTOR_TWO, 75);
    for(i = 0; i<1000; i++) delayUs(2000);
    setDutyCycle(MOTOR_ONE, 100);
    setDutyCycle(MOTOR_TWO, 100);
    for(i = 0; i<1000; i++) delayUs(2000);

    setDirection(MOTOR_ONE, REVERSE);
    setDirection(MOTOR_TWO, REVERSE);
    setDutyCycle(MOTOR_ONE, 50);
    setDutyCycle(MOTOR_TWO, 50);
    for(i = 0; i<1000; i++) delayUs(2000);
    setDutyCycle(MOTOR_ONE, 75);
    setDutyCycle(MOTOR_TWO, 75);
    for(i = 0; i<1000; i++) delayUs(2000);
    setDutyCycle(MOTOR_ONE, 100);
    setDutyCycle(MOTOR_TWO, 100);
    for(i = 0; i<1000; i++) delayUs(2000);

}