#include "Arduino.h"
#include "ptReadings.h"
#include "tcReadings.h"

static const int DE = 8;  // Control pin for MAX485
static const int RE = 9;  // Control pin for MAX485

void enableRS485Transmit();



void setup() {
    Serial1.begin(9600);

    pinMode(DE, OUTPUT);
    pinMode(RE, OUTPUT);

    initalizeADS(); //initalizes ads 1115
    initializeTC(); //initalizes max31855

    enableRS485Transmit(); 
}

void loop() {
    readPT();
    readTC();
    delay(500);
}

void enableRS485Transmit() { //recieves data from MAX485 to pc
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
}



