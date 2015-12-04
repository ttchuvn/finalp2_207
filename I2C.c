#include <proc/p32mx470f512l.h>

#include "lcd.h"
#include "I2C.h"
#include "timer.h"
#define WRITE 0
#define READ 1

#define VCNL4000_ADDRESS 0x13  // 0x26 write, 0x27 read
#define SCL TRISDbits.TRISD10 //I2C bus
#define SDA TRISDbits.TRISD9
#define SCL_IN PORTDbits.RD10
#define SDA_IN PORTDbits.RD9
// void I2C2_Init(void)
// {
// // --- I2C Control Register ---
// I2C2CONbits.I2CEN   = 0;// Disable I2C
// I2C2CONbits.I2CSIDL = 1; // Disable I2C in Idle Mode
// I2C2CONbits.SCLREL  = 1; // Release SCL
// I2C2CONbits.IPMIEN  = 1; // Disable IPMIEN
// I2C2CONbits.A10M    = 0; // 7-bit Slave Address
// I2C2CONbits.DISSLW  = 0; // Enable Slew Rate Control
// I2C2CONbits.SMEN    = 0; // Disable SMBus Thresholds
// I2C2CONbits.GCEN    = 0; // Disable General Call
// I2C2CONbits.STREN   = 0; // Disable Clock Stretching
// //I2C2CONbits.ACKDT   = 0; // Send Negative ACK During Acknowledgement
// I2C2CONbits.ACKDT   = 1; // Send NACK During Acknowledgement
// I2C2CONbits.ACKEN   = 0; // Acknowledge Sequence Not In Progress
// I2C2CONbits.RCEN    = 0; // Receive Sequence Not In Progress
// I2C2CONbits.PEN     = 0; // Stop Condition Not In Progress
// I2C2CONbits.RSEN    = 0; // Repeated Start Condition Not In Progress
// I2C2CONbits.SEN     = 0; // Start Condition Not In Progress 
// _MI2C2IE = 1; // Enable Master Interrupts
// _MI2C2IP = 1; // Interrupt Priority 6
// _MI2C2IF = 0; // Clear I2C Flag
// _SI2C2IE = 0; // Disable Slave Interrupts 
// I2C2BRG = 0x188; 
// I2C2CONbits.I2CEN = 1;   // Enable I2C
// } 
void initI2C(){
    SCL = 0;
    SDA = 0;
    SCL_IN = 0;
    SDA_IN = 0;
    I2C2CONbits.ON = 1; 
//    TRISBbits.TRISB2 = 0; //Sets those two I2C pins to output
//    TRISBbits.TRISB3 = 0;
//  AD1PCFGbits.PCFG4 = 1; //Configure those Pin to be digital
//  AD1PCFGbits.PCFG5 = 1;
    I2C2CONbits.I2CSIDL;
    I2C2CONbits.I2CSIDL = 0; //Stop in Idle Mode bit 0 = continue in idle mode
    I2C2CONbits.A10M = 0; //7 bit slave address
    I2C2CONbits.I2CEN = 1; //Enable Bit

    IFS1bits.I2C2MIF = 0; //Set the I2c interupt flag to 0
    I2C2BRG = 145;    
}

void writeByte(char reg, char data){
    beginTransmission(VCNL4000_ADDRESS); //Start Bit and slave address
    if(I2C2STATbits.ACKSTAT == 0){
        send(reg); //Sends Data to the device
    }
    if(I2C2STATbits.ACKSTAT == 0){
        send(data);
    }
    endTransmission(); //Outputs the stop bits
   
}
//Read Data from I2C device
unsigned char readByte(char reg){
    char c;

    beginTransmission(VCNL4000_ADDRESS);
    if(I2C2STATbits.ACKSTAT == 0){
        send(reg);
    }
    if(I2C2STATbits.ACKSTAT == 0){
        endTransmission();
    }
    requestFrom(VCNL4000_ADDRESS);
    if(I2C2STATbits.ACKSTAT == 0){
        I2C2CONbits.RCEN = 1;
        //while(I2C2CONbits.RCEN);
        while(I2C2STATbits.RBF == 0);
        c = I2C2RCV;
    }
    masterACK();
    endTransmission();
    return c;
}

//Start writing data
 void beginTransmission(char saddress){
    //Start bit
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
    //SlaveAddress
    I2C2TRN = saddress << 1 | WRITE;
    while(I2C2STATbits.TRSTAT == 1); //Wait for address to be sent
}
 void send(char address){
    I2C2TRN = address; //Send Slave address //Start transmitting when somethign is inserted
    while(I2C2STATbits.TRSTAT == 1); //Wait for address to be sent
 }
 void endTransmission(){
     I2C2CONbits.PEN = 1;    //Stop
     while(I2C2CONbits.PEN);
      delayUs(900);
 }
 //Starts the procedure to get information from the specefic sensor
void requestFrom(char saddress){
     //Start bit
    I2C2CONbits.SEN = 1;
    while(I2C2CONbits.SEN);
//    while(IFS3bits.MI2C2IF == 0);
//    IFS3bits.MI2C2IF = 0;

    I2C2TRN = saddress << 1 | READ;
    while(I2C2STATbits.TRSTAT == 1); //Wait for address to be sent
 }
//Master Acknowledgement
void masterACK(){
    I2C2CONbits.ACKDT = 1;
    I2C2CONbits.ACKEN = 1;
    while(IFS1bits.I2C2MIF == 0);
    IFS1bits.I2C2MIF = 0;
}

void checkIdle(){ //Checks if both master and slave are doing nothing
    while(I2C2CONbits.SEN  && I2C2CONbits.RSEN && I2C2CONbits.PEN && I2C2CONbits.RCEN && I2C2CONbits.ACKEN 
            && I2C2STATbits.TRSTAT );
}