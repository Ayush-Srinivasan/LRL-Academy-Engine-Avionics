#ifndef SENSORDATA_H
#define SENSORDATA_H

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
#include <SPI.h>
#include <Adafruit_MAX31855.h>

//constants
const int PSI = 300;
const float ADS_Gain = 0.1875/1000;
    //adc pins
extern Adafruit_ADS1115 ads1; //first ads 1115 (for pts 1-4) gnd connection (address 0x48)
extern Adafruit_ADS1115 ads2; //second ads 1115 (for pts 5-8) vdd connection (address 0x49)
extern const int adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8; 

    //max31855 spi pins
const int MISO = 12;
const int CLK = 27;
    
    //tc pin chip select numbers
const int TC1_CS = 0;
const int TC2_CS = 1;
const int TC3_CS = 2;
const int TC4_CS = 3;
const int TC5_CS = 4;
const int TC6_CS = 5; 

//time
extern unsigned long sensorStartTime;
extern unsigned long readTime;

//functions
float readPressureData(int16_t adcnumber, int PSI);
void readData();
void setupDataReading();

#endif
