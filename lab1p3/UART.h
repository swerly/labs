/* 
 * File:   initUART.h
 * Author: gvanhoy
 *
 * Created on December 30, 2014, 7:54 PM
 */

#ifndef INITUART_H
#define	INITUART_H

#define XTFREQ          7372800         	  // On-board Crystal frequency
#define PLLMODE         4               	  // On-chip PLL setting (Fosc)
#define FCY             (XTFREQ*PLLMODE)/2    // Instruction Cycle Frequency (Fosc/2)

#define BAUDRATE         115200
#define BRGVAL          ((FCY/BAUDRATE)/16)-1

void initUART();

#endif	/* INITUART_H */

