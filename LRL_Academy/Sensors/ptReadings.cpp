#include "Arduino.h"
#include "ptReadings.h"

//PT libraries
#include "Wire.h"
#include "Adafruit_ADS1X15.h"

//initalizing ads 1115
static Adafruit_ADS1115 ads1; //first ads 1115 (for pts 1-4) gnd connection (address 0x48)
static Adafruit_ADS1115 ads2; //second ads 1115 (for pts 5-8) vdd connection (address 0x49)
static const float ADS_Gain = 0.1875f / 1000.0f;

//pt port variables (0,1,2,3, are the adc ports)
static const int adc1 = 0; //AIN0 on ads1
static const int adc2 = 1; //AIN1 on ads1
static const int adc3 = 2; //AIN2 on ads1
//static const int adc4 = 3; //AIN3 on ads1

static const int adc5 = 0; //AIN0 on ads2
static const int adc6 = 1; //AIN1 on ads2
//static const int adc7 = 2; //AIN2 on ads2
//static const int adc8 = 3; //AIN3 on ads2

//pt values
float ptReadings[5];

// put function declarations here:
float readPressureData(int16_t adcnumber, int PSI);
void initalizeADS();
void readPT();
//void printPTReadings();


void initalizeADS() {
 //ads initialize
 if (!ads1.begin(0x48)) {
    Serial1.println("ADS1 failure");
    while(1);
  }
  ads1.setGain(GAIN_TWOTHIRDS);
  ads1.setDataRate(RATE_ADS1115_860SPS);
  
  if (!ads2.begin(0x49)) {
    Serial1.println("ADS2 failure");
    while(1);
  }
  ads2.setGain(GAIN_TWOTHIRDS);
    // ads.setGain(GAIN_TWOTHIRDS);  +/- 6.144V  1 bit = 0.1875mV (default)
  ads2.setDataRate(RATE_ADS1115_860SPS);
}

void readPT() {

    // ads read data
    int16_t PT1 = ads1.readADC_SingleEnded(adc1);
    int16_t PT2 = ads1.readADC_SingleEnded(adc2);
    int16_t PT3 = ads1.readADC_SingleEnded(adc3);
    //int16_t PT4 = ads1.readADC_SingleEnded(adc4);
    int16_t PT5 = ads2.readADC_SingleEnded(adc5);
    int16_t PT6 = ads2.readADC_SingleEnded(adc6);
    //int16_t PT7 = ads2.readADC_SingleEnded(adc7);
    //int16_t PT8 = ads2.readADC_SingleEnded(adc8);
  
  
    ptReadings[0] = readPressureData(PT1, 300);
    ptReadings[1] = readPressureData(PT2, 300);
    ptReadings[2] = readPressureData(PT3, 300);
    //ptReadings[3] = readPressureData(PT4, 300);
    ptReadings[3] = readPressureData(PT5, 300);
    ptReadings[4] = readPressureData(PT6, 300);
    //ptReadings[5] = readPressureData(PT7, 300);
    //ptReadings[7] = readPressureData(PT8, 300);

    Serial1.print("PT:");
    for (int i = 0; i < 5; i++) {
        Serial1.print(ptReadings[i]);
        if (i < 5) {
            Serial1.print(",");
        }
    }
    Serial1.println();

}

float readPressureData(int16_t adcnumber, int PSI) {
    float voltage = adcnumber * ADS_Gain; // multiplies ADS values by gain value
    float pressure = PSI * ((voltage-0.5)/4); //converts voltage to psi
    return pressure; //returns pressure
}

