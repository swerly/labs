#include "p24fj64ga002.h"
#include "UART.h"

void initUART(){
    // Set UART1's baud rate generator register (U1BRG) to the value calculated above.
    U1BRG  = BRGVAL;
    U1MODE = 0x8000;
    U1STA  = 0x0440; 		// Reset status register and enable TX & RX
    RPINR18bits.U1RXR = 9;
    RPOR4bits.RP8R = 3;
    IFS0bits.U1RXIF = 0;
}