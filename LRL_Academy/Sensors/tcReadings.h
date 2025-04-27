#ifndef TCREADINGS_H
#define TCREADINGS_H

//libraries
#include "Arduino.h"
#include "SPI.h"
#include "Adafruit_MAX31855.h"

extern float tcReadings[4];

//TC read and setup functions
void initalizeTC();
void readTC();

#endif