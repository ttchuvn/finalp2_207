/* 
 * File:   led.h
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */

#ifndef LED_H
#define	LED_H

void initLEDs();
void turnOnLED();
void turnOffLED(int led);
void assignColors();
void trackFollowing();
void robotBehaviors();

#define ON 0
#define OFF 1

#define OUTPUT 0
#define INPUT 1

#define BLACK 1
#define WHITE 0

#define THRESHOLD 500// threshold < 500 --> black else white

volatile int sensorLeft;
volatile int sensorMiddle;
volatile int sensorRight;
volatile unsigned int sensorLeftReading;
volatile unsigned int sensorMiddleReading;
volatile unsigned int sensorRightReading;
volatile unsigned int potADCVal; //pot

#endif	/* LED_H */

