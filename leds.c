/* 
 * File:   led.c
 * Author: gvanhoy
 * Team: 207
 * Created on August 27, 2015, 3:15 PM
 */

#include <xc.h>
#include "leds.h"
#include "adc.h"
#include "switch.h"
#include "lcd.h"
#include "VCNL4000.h"
typedef enum stateTypeEnum{
    IdleState, avoidState,lookForTrackState, turnLeftState, turnRightState, forwardState, turnAroundState, dbPress, waitForRelease, dbRelease
} stateType;

volatile stateType currState = IdleState;

void assignColors()
{
    if(currState != IdleState)
    {        
        sensorLeft = (sensorLeftReading < THRESHOLD) ? BLACK : WHITE;//sensor reading < threshold (500) --> black else white
        sensorMiddle = (sensorMiddleReading < THRESHOLD) ? BLACK : WHITE;
        sensorRight = (sensorRightReading < THRESHOLD) ? BLACK : WHITE;
    }
}
void trackFollowing()
{
    switch(currState)
       {
           case IdleState:
                IdleFunction();            
                if(!SW){currState = dbPress;}
                break;
            case dbPress:
                delayMs(10);
                currState = waitForRelease;
                break;
            case waitForRelease:
                if(!SW){currState = dbRelease;}
                break;
            case dbRelease:
                delayMs(10);
                currState = forwardState;
                break;            
            case lookForTrackState:
               lookForTrack();
               break;
            case forwardState:
               spinForward();
               break;
            case turnRightState:
               turnRight();
               break;
            case turnLeftState:
               turnLeft();
               break;            
            case turnAroundState:
               turnAround();
               //delayMs(10000);
               break;      
       }
}
void robotBehaviors()
{
    unsigned int prox = 0; //Holds the Proximity value from the Proximity Sensor
    if(currState!=IdleState)
    {
        prox = readProximity();
        if (prox >= proximity_Threshold)
            currState = avoidState;
       
       if(!sensorLeft && !sensorMiddle && !sensorRight) //000
       {

           currState = turnAroundState;
       }
       else if(!sensorLeft && !sensorMiddle && sensorRight) //001 can't occur
       {

           currState = turnRightState;
       }
       else if(!sensorLeft && sensorMiddle && !sensorRight) //010
       {

           currState = forwardState;
       }
       else if(!sensorLeft && sensorMiddle && sensorRight)//011
       {
           currState = turnRightState;
       }
       else if(sensorLeft && !sensorMiddle && !sensorRight) //100 cant occur
       {

           currState = turnLeftState;
       }
       else if(sensorLeft && !sensorMiddle && sensorRight) //101 cant occur
       {
           
           currState = forwardState;
       } 
       else if(sensorLeft && sensorMiddle && !sensorRight) //110
       {

           currState = turnLeftState;
       }
       else if(sensorLeft && sensorMiddle && sensorRight) //111
       {
           //currState = turnAroundState;
       }
    }
}
