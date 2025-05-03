#include <Arduino.h>
#include "tcReadings.h"

// Analog pins connected to AD8495 outputs
static const int tcPins[5] = {A0, A1, A2, A3, A4};

// Calibration parameters for each thermocouple
static float gainCorrection[5]   = {1.0, 1.0, 1.0, 1.0, 1.0};
static float offsetCorrection[5] = {6.7, 3.7, 4.7, -15.0, 0.8};

// AD8495 and ADC config
static const float adcRef = 5.0;
static const int adcResolution = 1023;
static const float offsetVoltage = 1.25;
static const float mvPerDegC = 5.0;

void initializeTC() {

  for (int i = 0; i < 5; i++) {
    pinMode(tcPins[i], INPUT);
  }
}

void readTC() {
  Serial1.print("TC: ");

  for (int i = 0; i < 5; i++) {
    int rawADC = analogRead(tcPins[i]);
    float voltage = (rawADC * adcRef) / adcResolution;
    float tempRaw = (voltage - offsetVoltage) * 1000.0 / mvPerDegC;
    float tempCalibrated = (tempRaw * gainCorrection[i]) + offsetCorrection[i];

    Serial1.print(tempCalibrated, 1);
    if (i < 5 - 1) Serial1.print(",");
  }
  Serial1.println();
}
