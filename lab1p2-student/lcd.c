/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

#include "p24fj64ga002.h"
#include "lcd.h"
#include "timer.h"

#define LCD_DATA   LATB
#define LCD_RS  LATBbits.LATB7
#define LCD_E   LATBbits.LATB6

#define LCD_D7 LATBbits.LATB15
#define LCD_D6 LATBbits.LATB14
#define LCD_D5 LATBbits.LATB13
#define LCD_D4 LATBbits.LATB12


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
    if (lower){
        LCD_D7 = word<3>;
        LCD_D6 = word<2>;
        LCD_D5 = word<1>;
        LCD_D4 = word<0>;
    }
    else {
        LCD_D7 = word<7>;
        LCD_D6 = word<6>;
        LCD_D5 = word<5>;
        LCD_D4 = word<4>;
    }
    LCD_RS = 1;

    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    writeFourBits(word, commandType, delayAfter, 0); // write upper 4 bits
    writeFourBits(word, commandType, delayAfter, 1); // write lower 4 bits
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    writeLCD(c, 1, )
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    TRIS_D7, TRIS_D6, TRIS_D5, TRIS_D4, TRIS_RS, TRIS_E = 0;
    // Initilization sequence utilizes specific LCD commands before the general configuration
    // commands can be utilized. The first few initilition commands cannot be done using the
    // WriteLCD function. Additionally, the specific sequence and timing is very important.

    //Wait 15ms after LCD turned on
    delayUs(15000);
    //=========================================================
    LCD_D4, LCD_D5 = 1; //set data bits 4,5 to high
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    delayUs(4100);//delay 4.1ms before next step
    //=========================================================
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    delayUs(100); //wait 100us or more
    //=========================================================
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low
    //=========================================================
    // Enable 4-bit interface
    LCD_D4 = 0; //set d4 low
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low
    //=========================================================
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    LCD_D7 = 1;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low
    //=========================================================
    LCD_D7 = 0;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    LCD_D7 = 1;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low
    //=========================================================
    LCD_D7 = 0;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    LCD_D4 = 1;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low
    //=========================================================
    LCD_D4 = 0;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    LCD_D6 = 1;
    LCD_E = 1; delayUs(1);//enable high
    LCD_E = 0; delayUs(1);//enable low

    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
        // Turn Display (D) Off
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.
    // TODO: Entry Mode Set
        // Set Increment Display, No Shift (i.e. cursor move)
    // TODO: Display On/Off Control
        // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {
    int i=0;

    for (i = 0; s[i] != '\0'; i++){
        printCharLCD(s[i]);
    }
}

/*
 * Clear the display.
 */
void clearLCD(){
}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    if (y){
        if (x == 1) 
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
    moveCursorLCD(1, 2);
    for(i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for(i = 0; i < 1000; i++) delayUs(1000);
}