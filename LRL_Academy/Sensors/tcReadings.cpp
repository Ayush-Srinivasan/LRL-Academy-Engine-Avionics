#include "Arduino.h"
#include "tcReadings.h"

//TC libraries and variables
#include "SPI.h"
#include "Adafruit_MAX31855.h"



//tc pin chip select numbers
static const int TC1_CS = 0;
static const int TC2_CS = 1;
static const int TC3_CS = 2;
static const int TC4_CS = 3;
static const int TC5_CS = 4;
static const int TC6_CS = 5;


//initalizing MAX31855
static Adafruit_MAX31855 tcInjector(TC1_CS);
static Adafruit_MAX31855 tcConverging1(TC2_CS);
static Adafruit_MAX31855 tcConverging2(TC3_CS);
static Adafruit_MAX31855 tcConverging3(TC4_CS);
static Adafruit_MAX31855 tcThroat(TC5_CS);
static Adafruit_MAX31855 tcDiverging(TC6_CS);

//final tc values
float tcReadings[6];
void readTC();
//void printTCReadings();

void initalizeTC() {
    //max initialize
  if (!tcInjector.begin()) {
    Serial1.println("TC1 failure");
    while (1);
  }
  if (!tcConverging1.begin()) {
    Serial1.println("TC2 failure");
    while (1);
  }
  if (!tcConverging2.begin()) {
    Serial1.println("TC3 failure");
    while (1);
  }
  if (!tcConverging3.begin()) {
    Serial1.println("TC4 failure");
    while (1);
  }
  if (!tcThroat.begin()) {
    Serial1.println("TC5 failure");
    while (1);
  }
  if (!tcDiverging.begin()) {
    Serial1.println("TC6 failure");
    while (1);
  }
}

void readTC() {
  // MAX31855 read data
  tcReadings[0] = tcInjector.readCelsius();
  tcReadings[1] = tcConverging1.readCelsius();
  tcReadings[2] = tcConverging2.readCelsius();
  tcReadings[3] = tcConverging3.readCelsius();
  tcReadings[4] = tcThroat.readCelsius();
  tcReadings[5] = tcDiverging.readCelsius();

  Serial1.print("TC:"); //prints all TC values in a csv format
  for (int i = 0; i < 6; i++) {
      Serial1.print(tcReadings[i]);
      if (i < 5) {
          Serial1.print(",");
      }
  } 
  Serial1.println();


}
