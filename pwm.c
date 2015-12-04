/* 
 * File:   pwm.c
 * Author: 207
 *
 * Created on October 18, 2015, 2:02 PM
 */


#include <sys/attribs.h>
#include <xc.h>
#include "pwm.h"
#include "timer.h"
#include "lcd.h"
void initWheel(){    
    //RIGHTWHEEL
    TRI_PIN0 = OUTPUT; //
    TRI_PIN1 = OUTPUT; //
    //LEFTWHEEL
    TRI_PIN2 = OUTPUT; //  
    TRI_PIN3 = OUTPUT; //
}        
void initPWM(){    
    //Init PWM for OC2
    OC2CON = 0x0000; // Turn off OC2 while doing setup.
    OC2R = 0x0000; // Initialize primary Compare Register
    OC2RS = 0x0000; // Initialize secondary Compare Register
    OC2CON = 0x0006; // Configure for PWM mode
    OC2CONSET = 0x8000; // Enable OC2
    
    //Init PWM for OC4
    OC4CON = 0x0000; // Turn off OC4 while doing setup.
    OC4R = 0x0000; // Initialize primary Compare Register
    OC4RS = 0x0000; // Initialize secondary Compare Register
    OC4CON = 0x0006; // Configure for PWM mode
    OC4CONSET = 0x8000; // Enable OC4      
}
void IdleFunction(){   
    
    //turn off the motors
    TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
    TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
    LAT_PIN0 = OUTPUT;LAT_PIN1 = OUTPUT;
    LAT_PIN2 = OUTPUT;LAT_PIN3 = OUTPUT;
    //OC2 RIGHT WHEEL (unmap all the pins))
    OC_PIN0 = 0b0000;OC_PIN1 = 0b0000;            
    //OC4 LEFTWHEEL (unmap all the pins))
    OC_PIN2 = 0b0000;OC_PIN3 = 0b0000;             
}
void spinForward(){
    // Turn on both motors at full power
    TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
    TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;         
    //OC2 RIGHT WHEEL
    OC_PIN0 = 0b0000;//very important
    OC_PIN1 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
    //OC4 LEFTWHEEL
    OC_PIN2 = 0b0000;//very important
    OC_PIN3 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
    OC4RS = 400; //RIGHT
    OC2RS = 400; //LEFT    
}
void turnLeft()
{
    // Turn off left wheel
    // Turn on right wheel at full power
     TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
     TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;         
     //OC2 RIGHT WHEEL
     OC_PIN0 = 0b0000;//very important
     OC_PIN1 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
     //OC4 LEFTWHEEL
     OC_PIN2 = 0b0000;//very important
     OC_PIN3 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
     OC4RS = 400; //RIGHT 250 - 5 works best for now
     OC2RS = 0; //LEFT    
}
void turnRight()
{   
    TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
    TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;         
    //OC2 RIGHT WHEEL
    OC_PIN0 = 0b0000;//very important
    OC_PIN1 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
    //LAT_PIN0 = 0x0000;//not really need it
    //OC4 LEFTWHEEL
    OC_PIN2 = 0b0000;//very important
    OC_PIN3 = 0b1011;//map the pin to 11. 11 is vanhoy magic number
    //LAT_PIN2 = 0x0000;//not really need it
    OC4RS = 0; //RIGHT
    OC2RS = 400; //LEFT
}
void lookForTrack()
{
   delayMs(10000);     
    OC4RS = 0; //RIGHT
    OC2RS = 0;
    TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
    TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
    //OC2 RIGHT WHEEL flip (map and unmap) the values of PIN0 and 1 to get the right wheel moving backward
    OC_PIN0 = 0b0000;//very important
    OC_PIN1 = 0b1011;    //11 is vanhoy magic number
    //LAT_PIN1 = 0x0000;
    //OC4 LEFTWHEEL--> flip (map and unmap) the values of PIN2 and 3 to get the left wheel moving backward
    OC_PIN2 = 0b0000;//very important
    OC_PIN3 = 0b1011;//11 is vanhoy magic number
    
    OC4RS = 150; //RIGHT
    OC2RS = 400; //LEFT
    delayMs(10);  

}
void turnAround()
{
    //delayMs(10000);     
    OC4RS = 0; //RIGHT
    OC2RS = 0;
    TRI_PIN0 = OUTPUT;TRI_PIN1 = OUTPUT;
    TRI_PIN2 = OUTPUT;TRI_PIN3 = OUTPUT;
    //OC2 RIGHT WHEEL flip (map and unmap) the values of PIN0 and 1 to get the right wheel moving backward
    OC_PIN0 = 0b0000;//very important
    OC_PIN1 = 0b1011;    //11 is vanhoy magic number
    //LAT_PIN1 = 0x0000;
    //OC4 LEFTWHEEL--> flip (map and unmap) the values of PIN2 and 3 to get the left wheel moving backward
    OC_PIN2 = 0b1011;//very important
    OC_PIN3 = 0b0000;//11 is vanhoy magic number
    
    OC4RS = 400; //RIGHT
    OC2RS = 500; //LEFT
    delayMs(10);    
}