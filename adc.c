/* 
 * File:   adc.c
 * Author: 207
 *
 * Created on October 18, 2015, 2:02 PM
 */

#include <sys/attribs.h>
#include <xc.h>
#include "adc.h"
void initADC()
{
    ANSELBbits.ANSB0 = 0; //pot PIN34 J11 
    ANSELEbits.ANSE5 = 0; //left led/sensor PIN7 J10 --> RE5 AN22
    ANSELBbits.ANSB8 = 0; //middle led/sensor PIN34 J10 --> AN9
    ANSELBbits.ANSB9 = 0; //right led/sensor PIN33 J10 --> RB8 AN8   
    AD1CON1bits.FORM = 0; // 16 unsigned integer
    AD1CON1bits.SSRC = 7; // Auto-convert mode
    AD1CON1bits.ASAM = 0; //turn off auto-sampling
    AD1CON2bits.VCFG = 0; // Use board refernece voltages
    AD1CON2bits.CSCNA = 0; // Disable scanning
    AD1CON2bits.SMPI = 0; // 1 burrito
    AD1CON2bits.ALTS = 0; // Only Mux A
    AD1CON3bits.ADRC = 0; // Use PBCLK
    AD1CON3bits.SAMC = 2; // 2 Tad per sample
    AD1CON3bits.ADCS = 1; // 4 times the PBCLK
    AD1CHSbits.CH0NA = 0; // Use Vref- as negative reference
    
    IFS0bits.AD1IF = 0; // Put down ADC flag
    IPC5bits.AD1IP = 7;
    IEC0bits.AD1IE = 0;
    
    AD1CON1bits.SAMP = 0;
    AD1CON1bits.DONE = 1;
    
    AD1CON1bits.ADON = 1; // turn on the ADC
}
int potADC() //pot
{
    int potADCVal=0;
    AD1CHSbits.CH0SA = 0;
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = 1;
    while(AD1CON1bits.DONE == 0);
    potADCVal = ADC1BUF0;
    AD1CON1bits.SAMP = 0;
    return potADCVal;
}

int leftSensorADC() //left phototransistor
{
    int leftADCVal=0; 
    AD1CHSbits.CH0SA = 22;//analog pin 7 on j10
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = 1;       
    while(AD1CON1bits.DONE == 0);
    leftADCVal = ADC1BUF0;
    AD1CON1bits.SAMP = 0; 
    return leftADCVal;
}
int middleSensorADC() //middle phototransistor
{ 
    int middleADCVal=0; 
    AD1CHSbits.CH0SA = 9;//analog pin 34 on j10
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = 1;      
    while(AD1CON1bits.DONE == 0);
    middleADCVal = ADC1BUF0;
    AD1CON1bits.SAMP = 0; 
    return middleADCVal;
}
int rightSensorADC() //right phototransistor
{    
    int rightADCVal=0; 
    AD1CHSbits.CH0SA = 8;//analog pin 33 on j10
    AD1CON1bits.SAMP = 1;
    AD1CON1bits.DONE = 1;       
    while(AD1CON1bits.DONE == 0);
    rightADCVal = ADC1BUF0;
    AD1CON1bits.SAMP = 0;
    return rightADCVal;
}