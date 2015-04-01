#include "p24FJ64GA002.h"
#include "pwm.h"
#include "timer.h"
#include "lcd.h"

#define PRVAL 56

//sets motor one to be going forward initially
void initMotorOnePWM(){

    OC1CONbits.OCTSEL = 1; //use TMR3
    OC1CONbits.OCM = 6; //set oc to pwm
    RPOR1bits.RP2R = 18; //map OC2 to pin 6 (RP2)
    RPOR1bits.RP3R = 0; //map

    TRISBbits.TRISB2 = OUTPUT;
    TRISBbits.TRISB3 = OUTPUT;
    ODCBbits.ODB3 = 1; //opposite side of the motor to odc

    OC1R = 0; //sets to the beginning of the period
    OC1RS = 0; //will change this later
}

//sets motor two to be going forward initially
void initMotorTwoPWM(){
    OC2CONbits.OCTSEL = 1; //use TMR3
    OC2CONbits.OCM = 6; //set oc to pwm
    RPOR5bits.RP10R = 19; //map OC1 to pin 21
    RPOR5bits.RP11R = 0; //map pin 22 to nothing

    TRISBbits.TRISB10 = OUTPUT;
    TRISBbits.TRISB11 = OUTPUT;
    ODCBbits.ODB11 = 1; //opposite side of the motor to odc

    OC2R = 0; //sets to the beginning of the period
    OC2RS = 0; //will change this later
}

void setDutyCycle(int motor, float percent){
    if (motor == MOTOR_ONE){
        OC1RS = (unsigned int)((percent/100)*PRVAL);
    }
    else if (motor == MOTOR_TWO){
        OC2RS = (unsigned int)((percent/100)*PRVAL);
    }
    else if (motor == BOTH){
        OC1RS = (unsigned int)((percent/100)*PRVAL);
        OC2RS = (unsigned int)((percent/100)*PRVAL);
    }
}

void setDirection(int motor, int dir){
    if (dir == FORWARD){

        if (motor == MOTOR_ONE){
            RPOR1bits.RP3R = 0; //map NOTHING to pin 7 (RP3)
            ODCBbits.ODB3 = 1; //turn on odc for pin 7
            ODCBbits.ODB2 = 0; //turn off odc for pin 6 (RP2)
            RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)
        }

        if (motor == MOTOR_TWO){
            RPOR5bits.RP11R = 0; //map pin 22 to nothing
            ODCBbits.ODB11 = 1; //turn on odc for pin 22
            ODCBbits.ODB10 = 0; //turn off odc for  pin 21 (RB10)
            RPOR5bits.RP10R = 19; //map OC2 to pin 21 (RP10)
        }

        if (motor == BOTH){
            RPOR1bits.RP3R = 0; //map NOTHING to pin 7 (RP3)
            ODCBbits.ODB3 = 1; //turn on odc for pin 7
            ODCBbits.ODB2 = 0; //turn off odc for pin 6 (RP2)
            RPOR1bits.RP2R = 19; //map OC2 to pin 6 (RP2)

            RPOR5bits.RP11R = 0; //map pin 22 to nothing
            ODCBbits.ODB11 = 1; //turn on odc for pin 22
            ODCBbits.ODB10 = 0; //turn off odc for  pin 21 (RB10)
            RPOR5bits.RP10R = 19; //map OC2 to pin 21
        }
    }
    else if (dir == REVERSE){

        if (motor == MOTOR_ONE){
            RPOR1bits.RP2R = 0; //map NOTHING to pin 6 (RP2)
            ODCBbits.ODB2 = 1; //turn on odc for pin 6
            ODCBbits.ODB3 = 0; //turn off odc for pin 7 (RP3)
            RPOR1bits.RP3R = 19; //map OC2 to pin 7 (RP3)
        }

        if (motor == MOTOR_TWO){
            RPOR5bits.RP10R = 0; //map pin 22 to nothing
            ODCBbits.ODB10 = 1; //turn on odc for pin 21
            ODCBbits.ODB11 = 0; //turn off odc for pin 22
            RPOR5bits.RP11R = 19; //map OC2 to pin
        }

        if (motor == BOTH){
            RPOR1bits.RP2R = 0; //map NOTHING to pin 6 (RP2)
            ODCBbits.ODB2 = 1; //turn on odc for pin 6
            ODCBbits.ODB3 = 0; //turn off odc for pin 7 (RP3)
            RPOR1bits.RP3R = 19; //map OC2 to pin 7 (RP3)

            RPOR5bits.RP10R = 0; //map pin 22 to nothing
            ODCBbits.ODB10 = 1; //turn on odc for pin 21
            ODCBbits.ODB11 = 0; //turn off odc for pin 22
            RPOR5bits.RP11R = 19; //map OC2 to pin
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