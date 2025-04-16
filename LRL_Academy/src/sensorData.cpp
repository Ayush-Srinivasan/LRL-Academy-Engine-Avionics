#include "Arduino.h"
#include "sensorData.h"

//PT libraries and variables
#include "Wire.h"
#include "Adafruit_ADS1X15.h"

//initalizing ads 1115
Adafruit_ADS1115 ads1; //first ads 1115 (for pts 1-4) gnd connection (address 0x48)
Adafruit_ADS1115 ads2; //second ads 1115 (for pts 5-8) vdd connection (address 0x49)
const float ADS_Gain = 0.1875/1000;

//pt port variables (0,1,2,3, are the adc ports)
const int adc1 = 0; //AIN0 on ads1
const int adc2 = 1; //AIN1 on ads1
const int adc3 = 2; //AIN2 on ads1
const int adc4 = 3; //AIN3 on ads1

const int adc5 = 0; //AIN0 on ads2
const int adc6 = 1; //AIN1 on ads2
const int adc7 = 2; //AIN2 on ads2
const int adc8 = 3; //AIN3 on ads2

//TC libraries and variables
#include "SPI.h"
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

//time
unsigned long sensorStartTime = 0;
unsigned long readTime = 500;

// put function declarations here:
float readPressureData(int16_t adcnumber, int PSI);
void readData();
void setupDataReading();

void setupDataReading() {

  //ads initialize
  if (!ads1.begin(0x48)) {
    Serial1.println("ADS1 failure");
    while(1);
  }
  ads1.setGain(GAIN_TWOTHIRDS);
  
  if (!ads2.begin(0x49)) {
    Serial1.println("ADS2 failure");
    while(1);
  }
  ads2.setGain(GAIN_TWOTHIRDS);
// ads.setGain(GAIN_TWOTHIRDS);  +/- 6.144V  1 bit = 0.1875mV (default)


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

void readData() {
  if (millis() - sensorStartTime >= readTime) {  
    sensorStartTime = millis();  // Reset the timer


  // ads read data
  int16_t PT1 = ads1.readADC_SingleEnded(adc1);
  int16_t PT2 = ads1.readADC_SingleEnded(adc2);
  int16_t PT3 = ads1.readADC_SingleEnded(adc3);
  int16_t PT4 = ads1.readADC_SingleEnded(adc4);
  int16_t PT5 = ads2.readADC_SingleEnded(adc5);
  int16_t PT6 = ads2.readADC_SingleEnded(adc6);
  int16_t PT7 = ads2.readADC_SingleEnded(adc7);
  int16_t PT8 = ads2.readADC_SingleEnded(adc8);


  //converts from voltage to psi 
  float PT01 = readPressureData(PT1, 300);
  float PT02 = readPressureData(PT2, 300);
  float PT03 = readPressureData(PT3, 300);
  float PT04 = readPressureData(PT4, 300);
  float PT05 = readPressureData(PT5, 300);
  float PT06 = readPressureData(PT6, 300);
  float PT07 = readPressureData(PT7, 300);
  float PT08 = readPressureData(PT8, 300);

  // MAX31855 read data
  float InjectorTemp = tcInjector.readCelsius();
  float Converging1Temp = tcConverging1.readCelsius();
  float Converging2Temp = tcConverging2.readCelsius();
  float Converging3Temp = tcConverging3.readCelsius();
  float ThroatTemp = tcThroat.readCelsius();
  float DivergingTemp = tcDiverging.readCelsius();  

 // print data (this will be changed when gui is available)

  Serial1.print("TC1: "); Serial1.println(InjectorTemp);
  Serial1.print("TC2: "); Serial1.println(Converging1Temp);
  Serial1.print("TC3: "); Serial1.println(Converging2Temp);
  Serial1.print("TC4: "); Serial1.println(Converging3Temp);
  Serial1.print("TC5: "); Serial1.println(ThroatTemp);
  Serial1.print("TC6: "); Serial1.println(DivergingTemp);
  Serial1.print("PT1: "); Serial1.println(PT01);
  Serial1.print("PT2: "); Serial1.println(PT02);
  Serial1.print("PT3: "); Serial1.println(PT03);
  Serial1.print("PT4: "); Serial1.println(PT04);
  Serial1.print("PT5: "); Serial1.println(PT05);
  Serial1.print("PT6: "); Serial1.println(PT06);
  Serial1.print("PT7: "); Serial1.println(PT07);
  Serial1.print("PT8: "); Serial1.println(PT08);
  Serial1.println("--------------------");
  }
  
}

float readPressureData(int16_t adcnumber, int PSI) {
  float voltage = adcnumber * ADS_Gain; // multiplies ADS values by gain value
  float pressure = PSI * ((voltage-0.5)/4); //converts voltage to psi
  return pressure; //returns pressure
}

