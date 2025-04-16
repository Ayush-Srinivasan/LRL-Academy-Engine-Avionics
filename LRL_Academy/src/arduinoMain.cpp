#include "Arduino.h"
#include "sensorData.h"

const int DE = 5;  // Control pin for MAX485
const int RE = 4;  // Control pin for MAX485

void receiveData();

void setup() {
    void setupDataReading();
    Serial1.begin(9600);
    recieveData();
}

void loop() {
    readData();
    delay(1000);
}

void recieveData() { //recieves data from MAX485 to pc
    digitalWrite(DE, HIGH);
    digitalWrite(RE, HIGH);
}