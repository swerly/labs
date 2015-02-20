#include "p24fj64ga002.h"
#include "initLEDs.h"

void initLEDs(){
    TRISBbits.TRISB15 = 0;
    TRISBbits.TRISB14 = 0;
    TRISBbits.TRISB13 = 0;
    TRISBbits.TRISB12 = 0;

    LATBbits.LATB15 = OFF;
    LATBbits.LATB14 = OFF;
    LATBbits.LATB13 = OFF;
    LATBbits.LATB12 = OFF;
}

void turnOnLED(int led){
    LATB |= 0xFFFF;
    LATB ^= (0x1 << (15 - (led - 4)));
}
