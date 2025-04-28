#ifndef TCREADINGS_H
#define TCREADINGS_H

//libraries
#include "Arduino.h"
#include "SPI.h"
#include "Adafruit_MAX31855.h"

extern float tcReadings[3];

//TC read and setup functions
void initializeTC();
void readTC();

#endif