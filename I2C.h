#ifndef I2C_H
#define	I2C_H

void initI2C();
unsigned char i2cRead(char i2cAddress);
void i2cWrite(char data, char i2cAddress);
void beginTransmission(char i2cAddress);
void send(char i2cAddress);
void endTransmission();
void requestFrom(char i2cAddress);
void masterACK();
void checkIdle();
#endif	/* I2C_H */
