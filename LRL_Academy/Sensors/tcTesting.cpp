#include "Arduino.h"
#include "tcReadings.h"

void setup(){
    Serial.begin(9600);
    initializeTC();
}

void loop() {
    readTC();
    delay(500);
}