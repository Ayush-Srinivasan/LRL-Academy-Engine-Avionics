#include <Arduino.h>

//PT libraries and variables
#include <Wire.h>
#include <Adafruit_ADS1X15.h>

//initalizing ads 1115
Adafruit_ADS1115 ads1; //first ads 1115 (for pts 1-4) gnd connection (address 0x48)
Adafruit_ADS1115 ads2; //second ads 1115 (for pts 5-8) vdd connection (address 0x49)

//pt port variables (0,1,2,3, are the adc ports)
const int PT1 = 0; //AIN0 on ads1
const int PT2 = 1; //AIN1 on ads1
const int PT3 = 2; //AIN2 on ads1
const int PT4 = 3; //AIN3 on ads1
const int PT5 = 0; //AIN0 on ads1
const int PT6 = 1; //AIN1 on ads1
const int PT7 = 2; //AIN2 on ads1
const int PT8 = 3; //AIN3 on ads1

//TC libraries and variables
#include <SPI.h>
#include "Adafruit_MAX31855.h"
const int MISO = 12;
const int CLK = 27;

//tc pin chip select numbers
const int TC1_CS = 0;
const int TC2_CS = 1;
const int TC3_CS = 2;
const int TC4_CS = 3;
const int TC5_CS = 4;
const int TC6_CS = 5;


//initalizing MAX31855
Adafruit_MAX31855 tcInjector(TC1_CS, CLK, MISO);
Adafruit_MAX31855 tcConverging1(TC2_CS, CLK, MISO);
Adafruit_MAX31855 tcConverging2(TC3_CS, CLK, MISO);
Adafruit_MAX31855 tcConverging3(TC4_CS, CLK, MISO);
Adafruit_MAX31855 tcThroat(TC5_CS, CLK, MISO);
Adafruit_MAX31855 tcDiverging(TC6_CS, CLK, MISO);

// put function declarations here:


void setup() {
  Serial.begin(115200);

  //ads initialize
  if (!ads1.begin(0x48)) {
    Serial.println("ADS1 failure");
    while(1);
  }
  if (!ads2.begin(0x49)) {
    Serial.println("ADS2 failure");
    while(1);
  }

  //max initialize
  if (!tcInjector.begin()) {
    Serial.println("TC1 failure");
    while (1);
  }
  if (!tcConverging1.begin()) {
    Serial.println("TC2 failure");
    while (1);
  }
  if (!tcConverging2.begin()) {
    Serial.println("TC3 failure");
    while (1);
  }
  if (!tcConverging3.begin()) {
    Serial.println("TC4 failure");
    while (1);
  }
  if (!tcThroat.begin()) {
    Serial.println("TC5 failure");
    while (1);
  }
  if (!tcDiverging.begin()) {
    Serial.println("TC6 failure");
    while (1);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
}