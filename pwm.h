/* 
 * File:   pwm.h
 * Author: 207
 *
 * Created on October 18, 2015, 2:02 PM
 */

#ifndef PWM_H
#define	PWM_H

#define INPUT   1
#define OUTPUT  0
    
//OC2  RIGHTWHEEL
#define TRI_PIN0  TRISDbits.TRISD0     //TRI   
#define TRI_PIN1  TRISDbits.TRISD1       
#define LAT_PIN0  LATDbits.LATD0        //LAT
#define LAT_PIN1  LATDbits.LATD1
#define OC_PIN0   RPD1Rbits.RPD1R   //OC2
#define OC_PIN1   RPD8Rbits.RPD8R

//OC4  LEFTWHEEL
#define TRI_PIN2  TRISDbits.TRISD2  //TRI      
#define TRI_PIN3  TRISDbits.TRISD3       
#define LAT_PIN2  LATDbits.LATD2 //LAT
#define LAT_PIN3  LATDbits.LATD3
#define OC_PIN2   RPD3Rbits.RPD3R   //OC4
#define OC_PIN3   RPD11Rbits.RPD11R
    
#define RIGHTWHEEL OC2RS 
#define LEFTWHEEL OC4RS 

void initPWM();
void initWheel();
void spinForward();
void spinBackward();
void turnRight();
void turnLeft();
void IdleFunction();
void lookForTrack();
void turnAround();

#endif	/* PWM_H */