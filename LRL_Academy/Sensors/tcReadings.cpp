#include "Arduino.h"
#include "tcReadings.h"

//TC libraries and variables
#include "SPI.h"
#include "Adafruit_MAX31855.h"



//tc pin chip select numbers
static const int TC1_CS = 0;
static const int TC2_CS = 1;
static const int TC3_CS = 2;



//initalizing MAX31855
static Adafruit_MAX31855 tcChamber(TC1_CS);
static Adafruit_MAX31855 tcConverging(TC2_CS);
static Adafruit_MAX31855 tcThroat(TC3_CS);


//final tc values
float tcReadings[3];
void readTC();
//void printTCReadings();

void initializeTC() {
    //max31855 initialize
  if (!tcChamber.begin()) {
    Serial1.println("Chamber TC failure");
    while (1);
  }
  if (!tcConverging.begin()) {
    Serial1.println("Converging TC failure");
    while (1);
  }
  if (!tcThroat.begin()) {
    Serial1.println("Throat TC failure");
    while (1);
  }

}


void readTC() {
  // MAX31855 read data
  tcReadings[0] = tcChamber.readCelsius();
  tcReadings[1] = tcConverging.readCelsius();
  tcReadings[2] = tcThroat.readCelsius();

  Serial1.print("TC:"); //prints all TC values in a csv format
  for (int i = 0; i < 3; i++) {
      Serial1.print(tcReadings[i]);
      if (i < 2) {
          Serial1.print(",");
      }
  } 

  Serial1.println();
}
