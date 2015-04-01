/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"

#define LOWER 1
#define UPPER 0

#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define WRITE_DATA 1
#define SEND_COMMAND 0

#define LCD_DDRAM 0x80
#define LCD_ROW2 0x40

#define TRIS_D7  TRISBbits.TRISB15
#define TRIS_D6  TRISBbits.TRISB14
#define TRIS_D5  TRISBbits.TRISB13
#define TRIS_D4  TRISBbits.TRISB12
#define TRIS_RS  TRISBbits.TRISB7
#define TRIS_E   TRISBbits.TRISB6

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO: use bit shifting instead of single bit operations
    if(lower){
        //change data pins to 0, then or them with top 4 bits
        LCD_DATA = (LCD_DATA & 0x0FFF) | ((word & 0x0F)<<12);//shift to get into latb 15-12
    }
    else{
        LCD_DATA = (LCD_DATA & 0x0FFF) | ((word & 0xF0)<<8);//shift to get into latb 15-12
    }
    LCD_RS = commandType; delayUs(1);

    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; //enable low

    delayUs(delayAfter);

}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    writeFourBits(word, commandType, delayAfter, UPPER); // write upper 4 bits
    writeFourBits(word, commandType, delayAfter, LOWER); // write lower 4 bits
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    writeLCD(c, WRITE_DATA, 46);
}
/*Initialize the LCD*/
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7 = 0;
    TRIS_D6 = 0;
    TRIS_D5 = 0;
    TRIS_D4 = 0;
    TRIS_RS = 0;
    TRIS_E = 0;
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    //Wait 15ms after LCD turned on
    delayUs(15000);
    //=========================================================
    writeFourBits(0x03, SEND_COMMAND, 4100, LOWER);//0011
    //=========================================================
    writeFourBits(0x03, SEND_COMMAND, 100, LOWER);//0011
    //=========================================================
    writeFourBits(0x03, SEND_COMMAND, 40, LOWER);//0011
    //=========================================================
    writeFourBits(0x02, SEND_COMMAND, 40, LOWER);//0010
    //=========================================================
    writeFourBits(0x02, SEND_COMMAND, 40, LOWER);//0010

    writeFourBits(0x08, SEND_COMMAND, 40, LOWER);//1010
    //=========================================================
    writeFourBits(0x00, SEND_COMMAND, 40, LOWER);//0000

    writeFourBits(0x08, SEND_COMMAND, 40, LOWER);//1000 0x08
    //=========================================================
    writeFourBits(0x00, SEND_COMMAND, 40, LOWER);//0000

    writeFourBits(0x01, SEND_COMMAND, 1640, LOWER);//0001
    //=========================================================
    writeFourBits(0x00, SEND_COMMAND, 40, LOWER);//0000

    writeFourBits(0x06, SEND_COMMAND, 40, LOWER);//0110
    //=========================================================
    writeFourBits(0x01, SEND_COMMAND, 40, UPPER);

    writeFourBits(0x01, SEND_COMMAND, 1640, LOWER);
    //=========================================================
    writeFourBits(0x0C, SEND_COMMAND, 40, UPPER);

    writeFourBits(0x0C, SEND_COMMAND, 40, LOWER);


    //
    //DONE



}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    int i=0;

    //while we haven't reached the null char at the end of a string
    for (i = 0; s[i] != '\0'; i++){
        printCharLCD(s[i]);
    }
}

/*
 * Clear the display.
 */
void clearLCD(){
    writeFourBits(0x01, SEND_COMMAND, 40, UPPER);
    writeFourBits(0x01, SEND_COMMAND, 1640, LOWER);
}

void clearCursor(){
    writeFourBits(0x0E, SEND_COMMAND, 40, UPPER);
    writeFourBits(0x0E, SEND_COMMAND, 40, LOWER);
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    //if in the top row

    if (x == 0){
        writeLCD((LCD_DDRAM | y), SEND_COMMAND, 50);
    }
    else {
        writeLCD((LCD_DDRAM | y | LCD_ROW2), SEND_COMMAND, 50);
    }
}


/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD(){
    initLCD();

    int i = 0;
    printCharLCD('c');
    for(i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(2, 1);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);

}
