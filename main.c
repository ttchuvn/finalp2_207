/* 
 * File:   main.c
 * Author: 207
 *
 * Created on November 9, 2015, 2:02 PM
 */
#include <sys/attribs.h>
#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "interrupt.h"
#include "lcd.h"
#include "config.h"
#include "timer.h"
#include "pwm.h"
#include "switch.h"
#include "leds.h"
#include "VCNL4000.h"
#include "I2C.h"




typedef enum robotTypeEnum{
    robotMoving, robotTurnsAround
}robotType;


volatile robotType robot = robotMoving;

char str[16];

int main(void)
{
    unsigned int prox1 = 0;
    SYSTEMConfigPerformance(40000000);
    enableInterrupts(); 
    initADC(); 
    initPWM();
    initLCD();        
    initTimer3(); 
    initWheel(); 
    initI2C();//initialize I2C for external sensor
    initVCNL4000();//initialize the sensor with the correct sensor to start working properly
    clearLCD();
    prox1 = readProximity();    
    //prox1 = 3000;
    sprintf(str, "  %u", prox1); 
    moveCursorLCD(0,1);
    printStringLCD(str);
    while(1)
    {
//       prox1 = readProximity();
//       //prox1 = 5;
//       sprintf(str, "  %d", prox1);
//       moveCursorLCD(0,1);
//       printStringLCD("4");       
       potADCVal = potADC(); 
       sensorLeftReading = leftSensorADC();
       sensorMiddleReading = middleSensorADC();
       sensorRightReading = rightSensorADC();               
       moveCursorLCD(0,1);
//       sprintf(str, "  %d", potADCVal); 
//       printStringLCD(str);       
//       moveCursorLCD(0,2);
//       sprintf(str, "%d:%d:%d", sensorLeftReading/10, sensorMiddleReading/10, sensorRightReading/10);
//       printStringLCD(str);       
       assignColors(); 
       robotBehaviors();       
       switch(robot)
       {
           case robotMoving:
               trackFollowing();
               break;
           case robotTurnsAround:               
//               robot = robotMoving;
//               delayMs(10000);
               break;      
       }       
    }
    return 0;
}

int readAmbient1(){
     int data;
//    unsigned char temp;
//
//    temp = i2cRead(COMMAND_0);
//    i2cWrite(COMMAND_0, 0b10010000 /*temp | 0x10*/); // command the sensor to perform ambient measure
//
//    while(!(i2cRead(COMMAND_0)&0b01000000) /*0x20*/); // wait for the proximity data ready bit to be set
//    data = i2cRead(AMBIENT_RESULT_MSB) << 8;
//    data |= i2cRead(AMBIENT_RESULT_LSB);
    data = 3000;
    return data;
}