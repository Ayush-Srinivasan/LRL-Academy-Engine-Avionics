#include "Arduino.h"
#include "ptReadings.h"

void setup(){
    Serial.begin(9600);
    initalizeADS();
}

void loop() {
    readPT();
    printPTReadings();
    delay(500);
}