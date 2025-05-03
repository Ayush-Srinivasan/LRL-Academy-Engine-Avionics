#ifndef TCREADINGS_H
#define TCREADINGS_H

#include "Arduino.h"

// Initialize thermocouple system
void initializeTC();

// Read all thermocouples and print to Serial1
void readTC();

#endif  // TCREADINGS_H