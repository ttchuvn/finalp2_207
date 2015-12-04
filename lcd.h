/* 
 * File:   lcd.h
 * Author: 207
 *
 * Created on October 18, 2015, 2:02 PM
 */


void writeLCD(unsigned char word, unsigned int commandType, unsigned int delay);
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower);
void initLCD(void);
void clearLCD(void);
void moveCursorLCD(unsigned char x, unsigned char y);
void printCharLCD(char c);
void printStringLCD(const char* s);
void testLCD();