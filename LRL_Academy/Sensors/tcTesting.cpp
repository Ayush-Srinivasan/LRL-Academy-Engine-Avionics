#include "Arduino.h"
#include "tcReadings.h"

void setup(){
    Serial.begin(9600);
    initalizeTC();
}

void loop() {
    readTC();
    delay(500);
}