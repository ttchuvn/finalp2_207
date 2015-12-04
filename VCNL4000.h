

#ifndef VCNL4000_H
#define	VCNL4000_H

void initVCNL4000();
unsigned int readProximity();
unsigned int readAmbient();
#define proximity_Threshold 2270


#endif	/* VCNL4000_H */