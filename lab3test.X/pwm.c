#include "p24FJ64GA002.h"
#include "pwm.h"

#define PRVAL 56

//initiates PWM to control the LCD contrast
void initLCDPWM(){
    T3CONbits.TCKPS = 256;
    TMR3 = 0;
    PR3 = PRVAL;

    TRISBbits.TRISB11 = 0;
    OC1CONbits.OCTSEL = 1; //use TMR3
    OC1CONbits.OCM = 6; //set oc to pwm
    RPOR5bits.RP11R = 18; //map OC1 to pin22 (rp11)

    OC1R = 0; //sets to the beginning of the period
    OC1RS = 10; //~.9 volts give the best display contrast
    T3CONbits.TON = 1;
}

//sets motor one to be going forward initially
void initMotorOnePWM(){
    OC2CONbits.OCTSEL = 1; //use TMR3
    OC2CONbits.OCM = 6; //set oc to pwm
    RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    ODCBbits.ODB3 = 1; //opposite side of the motor to odc

    OC2R = 0; //sets to the beginning of the period
    OC2RS = 28; //will change this later
}

//sets motor two to be going forward initially
void initMotorTwoPWM(){
    OC3CONbits.OCTSEL = 1; //use TMR3
    OC3CONbits.OCM = 6; //set oc to pwm
    RPOR4bits.RP8R = 20; //map OC3 to pin 17 (RP8)

    TRISBbits.TRISB8 = 0;
    TRISBbits.TRISB9 = 0;
    ODCBbits.ODB9 = 1;

    OC3R = 0; //sets to the beginning of the period
    OC3RS = 0; //will change this later
}

void setDutyCycle(int motor, int percent){
    //TODO: use oscope to test output of the pins!!!!!!

    if (motor == MOTOR_ONE){
        OC2RS = (percent/100)*PRVAL;
    }
    else if (motor == MOTOR_TWO){
        OC3RS = (percent/100)*PRVAL;
    }
    else if (motor == LCD_VL){
        OC1RS = (percent/100)*PRVAL;
    }
}

void setDirection(int dir){
    if (dir == FORWARD){
        ODCBbits.ODB3 = 1; //opposite terminal of the motor to odc
        ODCBbits.ODB2 = 0; //turn off odc for pin 6 (RP2)
        RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

        ODCBbits.ODB9 = 1; //turn on odc for pin 18
        ODCBbits.ODB8 = 0; //turn off odc for pin 17
        RPOR4bits.RP8R = 20; //map OC3 to pin 17 (RP8)

    }
    else if (dir == REVERSE){
        ODCBbits.ODB2 = 1; //opposite terminal of the motor to odc
        ODCBbits.ODB3 = 0; //turn off odc for pin 7 (RP3)
        RPOR1bits.RP3R = 19; //map OC2 to pin 7 (RP3)

        ODCBbits.ODB8 = 1; //turn on odc for pin 17
        ODCBbits.ODB9 = 0; //turn off odc for pin 18
        RPOR4bits.RP9R = 20; //map OC3 to pin 18 (RP9)
    }
    delayUs(5); //delay so pins have time to change
}

void testMotors(){
    //test motors going forward and ramping up speed
    setDirection(FORWARD);
    setDutyCycle(MOTOR_ONE, 25);
    setDutyCycle(MOTOR_TWO, 25);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 50);
    setDutyCycle(MOTOR_TWO, 50);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 75);
    setDutyCycle(MOTOR_TWO, 75);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 100);
    setDutyCycle(MOTOR_TWO, 100);
    delayUs(2000);

    //stop
    setDutyCycle(MOTOR_ONE, 0);
    setDutyCycle(MOTOR_TWO, 0);
    delayUs(2000);

    //REVERSE AND REPEAT RAMPING UP
    setDirection(REVERSE);
    setDutyCycle(MOTOR_ONE, 25);
    setDutyCycle(MOTOR_TWO, 25);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 50);
    setDutyCycle(MOTOR_TWO, 50);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 75);
    setDutyCycle(MOTOR_TWO, 75);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 100);
    setDutyCycle(MOTOR_TWO, 100);
    delayUs(2000);
}

void testPWM(){
    setDirection(FORWARD);
    setDutyCycle(MOTOR_ONE, 25);
    delayUs(2000);
    setDutyCycle(MOTOR_ONE, 50);
    delayUs(2000);
    setDutyCycle(MOTOR_TWO, 75);
    delayUs(2000);


}