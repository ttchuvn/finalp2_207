/* 
 * File:   lcd.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:32 PM
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define OUTPUT 0
#define INPUT 1

#define UPPER 1
#define LOWER 0

#define CHARACTER 1

#define TRIS_RS   TRISGbits.TRISG14
#define TRIS_RW   TRISGbits.TRISG12 
#define TRIS_E    TRISGbits.TRISG15

#define TRIS_D4   TRISCbits.TRISC1
#define TRIS_D5   TRISDbits.TRISD10
#define TRIS_D6   TRISDbits.TRISD4
#define TRIS_D7   TRISEbits.TRISE0

#define LCD_DATA  LATB         // board
#define LCD_RS    LATGbits.LATG14 //4    4 on LCD
#define LCD_RW    LATGbits.LATG12 //3    5 on LCD 
#define LCD_E     LATGbits.LATG15 //1    6 on LCD

#define LCD_D4    LATCbits.LATC1 //18    11 on LCD
#define LCD_D5    LATDbits.LATD10 //16   12 on LCD
#define LCD_D6    LATDbits.LATD4 //14    13 on LCD  
#define LCD_D7    LATEbits.LATE0 //12    14 on LCD

void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower){
    //TODO:
    word = (!lower) ? word>>4 : word;//write upper
    LCD_RS = (commandType) ? INPUT : OUTPUT; //set commandType
    delayUs(1);
    LCD_D7 = (word>>3) & 1; 
    LCD_D6 = (word>>2) & 1;
    LCD_D5 = (word>>1) & 1;
    LCD_D4 = word & 1; //and  with 1 to get left most bit        
    LCD_E = INPUT;
    delayUs(1);
    LCD_E = OUTPUT; 
    delayUs(delayAfter);
}
/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter){
    //TODO:
    writeFourBits(word, commandType, delayAfter,LOWER); //write lower
    writeFourBits(word, commandType, delayAfter,UPPER); //write upper
}
/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c,CHARACTER, 40);
}
/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).    
    TRIS_D7 = OUTPUT;TRIS_D6 = OUTPUT;TRIS_D5 = OUTPUT; TRIS_D4 = OUTPUT;
    TRIS_RS = OUTPUT;TRIS_E = OUTPUT; 
    TRIS_RW = OUTPUT; LCD_RW = OUTPUT;

    int i;
    for(i=0;i<3;i++)
        delayUs(5000); //3*5000=15000 delay 15ms   
    writeFourBits(0b000011, 0, 40, 1); //000011
    delayUs(4100); // wait for 4.1ms or more
    writeFourBits(0b000011, 0, 40, 1); //000011
    delayUs(100); //wait 100us or more
    writeFourBits(0b000011, 0, 40, 1); //000011 functioni set 4 bits
    writeFourBits(0b000010, 0, 40, 1); //000010 functioni set 4 bits 
    
    writeLCD(0b101011, 0, 40);
    writeLCD(0b001000, 0, 40);    
    clearLCD();
    writeLCD(0b000110, 0, 40);
    writeLCD(0b001100, 0, 40);

}

void printStringLCD(const char* s) {
    //TODO:
    while(*s != '\0')
    {
        printCharLCD(*s);
        s+=1;        
    }    
}
/*
 * Clear the display.
 */
void clearLCD(){
    writeLCD(0b000001, 0, 1640);
}
/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 */
void moveCursorLCD(unsigned char x, unsigned char y){
    if (y == 2)
        writeLCD(x+0x80+0x40,0, 40);//write the second line
    else     
        writeLCD(x+0x80,0, 40);//write the first line
}

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
