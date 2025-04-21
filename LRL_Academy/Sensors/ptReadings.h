#ifndef PTREADINGS_H
#define PTREADINGS_H

//PT libraries
#include "Arduino.h"
#include "Wire.h"
#include "Adafruit_ADS1X15.h"


//functions 
float readPressureData(int16_t adcnumber, int PSI);
void initalizeADS();
void readPT();



#endif