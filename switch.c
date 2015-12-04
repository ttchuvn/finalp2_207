/*
 * File:   switch.c
 * Author: TEAM 207
 *
 */

#include <xc.h>
#include "switch.h"

#define INPUT 1
#define OUTPUT 0
#define ENABLED 1
#define DISABLED 0

void initSW(){
    TRIPOT = INPUT; //input
    TRISDbits.TRISD6 = INPUT;           // Configure switch as input
    CNCONDbits.ON = 1;                  // Enable overall interrupt
    CNENDbits.CNIED6 = ENABLED;         // Enable pin CN
    CNPUDbits.CNPUD6 = ENABLED;         // Enable pull-up resistor
    IFS1bits.CNDIF = 0;                 // Put down the flag
    IPC8bits.CNIP = 7;                  // Configure interrupt priority
    IEC1bits.CNDIE = ENABLED;           // Enable interrupt for D pins
}