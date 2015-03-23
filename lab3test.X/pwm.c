#include "p24FJ64GA002.h"
#include "pwm.h"

#define PRVAL 56

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

void initMotorOnePWM(){
    OC2CONbits.OCTSEL = 1; //use TMR3
    OC2CONbits.OCM = 6; //set oc to pwm
    RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB3 = 0;
    ODCBbits.ODB3 = 1; //opposite side of the motor to odc

    OC2R = 0; //sets to the beginning of the period
    OC2RS = 0; //will change this later
}

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
        ODCBbits.ODB3 = 1; //opposite side of the motor to odc
        ODCBbits.ODB2 = 0; //turn off odc for pin 6 (RP2)
        RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

        ODCBbits.ODB9 = 1; //turn on odc for pin 18
        ODCBbits.ODB8 = 0; //turn off odc for pin 17
        RPOR4bits.RP8R = 20; //map OC3 to pin 17 (RP8)

    }
    else if (dir == BACKWARD){
        ODCBbits.ODB2 = 1; //opposite side of the motor to odc
        ODCBbits.ODB3 = 0; //turn off odc for pin 7 (RP3)
        RPOR1bits.RP3R = 19; //map OC2 to pin 7 (RP3)

        ODCBbits.ODB8 = 1; //turn on odc for pin 17
        ODCBbits.ODB9 = 0; //turn off odc for pin 18
        RPOR4bits.RP9R = 20; //map OC3 to pin 18 (RP9)
    }
}