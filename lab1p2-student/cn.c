#include "p24fj64ga002.h"
#include "cn.h"

void initCNForSW1(){
    //Use the switch on the board connected to RB5
    TRISBbits.TRISB5 = 1;
    IFS1bits.CNIF = 1;
    IEC1bits.CNIE = 1;
    CNEN2bits.CN27IE = 1;
}