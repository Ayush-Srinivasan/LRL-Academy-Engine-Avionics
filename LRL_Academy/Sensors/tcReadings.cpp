#include "Arduino.h"
#include "tcReadings.h"

//TC libraries and variables
#include "SPI.h"
#include "Adafruit_MAX31855.h"

//static const int MISO = 12; //MISO Pin (dont need as hardware sets it)
//static const int CLK = 27; //CLOCK Pin (dont need as hardware sets it)

//tc pin chip select numbers
static const int TC1_CS = 0;
static const int TC2_CS = 1;
static const int TC3_CS = 2;
static const int TC4_CS = 3;
static const int TC5_CS = 4;
static const int TC6_CS = 5;


//initalizing MAX31855
static Adafruit_MAX31855 tcInjector(TC1_CS /*, CLK, MISO*/);
static Adafruit_MAX31855 tcConverging1(TC2_CS /*, CLK, MISO*/);
static Adafruit_MAX31855 tcConverging2(TC3_CS /*, CLK, MISO*/);
static Adafruit_MAX31855 tcConverging3(TC4_CS /*, CLK, MISO*/);
static Adafruit_MAX31855 tcThroat(TC5_CS /*, CLK, MISO*/);
static Adafruit_MAX31855 tcDiverging(TC6_CS /*, CLK, MISO*/);

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
  float InjectorTemp = tcInjector.readCelsius();
  float Converging1Temp = tcConverging1.readCelsius();
  float Converging2Temp = tcConverging2.readCelsius();
  float Converging3Temp = tcConverging3.readCelsius();
  float ThroatTemp = tcThroat.readCelsius();
  float DivergingTemp = tcDiverging.readCelsius(); 

  Serial1.print("Injector Temperature: "); Serial1.println(InjectorTemp);
  Serial1.print("Top Wall Temp: "); Serial1.println(Converging1Temp);
  Serial1.print("Middle Wall Temp: "); Serial1.println(Converging2Temp);
  Serial1.print("Bottom Wall Temp: "); Serial1.println(Converging3Temp);
  Serial1.print("Throat Temp: "); Serial1.println(ThroatTemp);
  Serial1.print("Exit Fuel Temp: "); Serial1.println(DivergingTemp);
}