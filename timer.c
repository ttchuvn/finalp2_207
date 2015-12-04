/* 
 * File:   timer.c
 * Author: 207
 *
 * Created on October 18, 2015, 2:02 PM
 */

#include <sys/attribs.h>
#include <xc.h>
#include "timer.h"
//Uses timer 2
void delayUs(unsigned int delay){
    
    TMR2 = 0x0000; //reset Timer2
    PR2 = delay * 14; 
    T2CONbits.TCKPS = 0; //pre-scalar = 1
    IFS0bits.T2IF = 0; //put Timer2 interrupt flag down
    T2CONbits.TON = 1; //turn on Timer2
    while(IFS0bits.T2IF == 0);
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 0; //turn off Timer2
    
}
//use timer2 for delayMs
void delayMs(unsigned int delay){
    
    TMR2 = 0x000; //reset the timer
    PR2 = delay*8; //delay in seconds
    T2CONbits.TCKPS = 0; //pre-scalar = 1
    IFS0bits.T2IF = 0; 
    T2CONbits.TON = 1; //turn on Timer2
    while(IFS0bits.T2IF == 0); 
    IFS0bits.T2IF = 0;
    T2CONbits.TON = 0; //turn off Timer2
}
//use timer3 for speed
void initTimer3()
{
    TMR3 = 0x0000; //clear TMR3
    T3CONbits.ON = 0; //turn timer off
    T3CONbits.SIDL = 0;    
    T3CONbits.TGATE = 0;
    T3CONbits.TCS = 0;     
    PR3 = 1023; //1023 for speed    
    T3CONbits.TCKPS2 = 1;
    T3CONbits.TCKPS1 = 1;
    T3CONbits.TCKPS0 = 1;    
    T3CONbits.ON = 1; //turn timer on
}
