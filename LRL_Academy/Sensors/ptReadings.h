#ifndef PTREADINGS_H
#define PTREADINGS_H

//PT libraries
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_ADS1X15.h"

extern float ptReadings[6];

//functions 
float readPressureData(int16_t adcnumber, int PSI);
void initalizeADS();
void readPT();


#endif