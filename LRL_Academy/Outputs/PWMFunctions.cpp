#include <Arduino.h>
#include <PWMServo.h>
#include "PWMFunctions.h"

//pwm pins for servos
static const int S1 = 3;
static const int S2 = 2;
static const int S3 = 1;
static const int S4 = 0;
static const int S5 = 7;
static const int S6 = 6;
static const int S7 = 5;
static const int S8 = 4;

//servo outputs
PWMServo mainFuelBallValve; // fuel inlet ball valve (0)
PWMServo outletFuelBallValve; // fuel outlet ball valve (1)
PWMServo oxidizerFuelBallValve; // gox ball valve (2)
PWMServo turbine1Valve; // turbine 1 N2 valve (3)
PWMServo turbine2Valve; // turbine 2 N2 valve (4)
PWMServo airBleedValve; // air bleed valve servo output (5)
const int openPositions[6] = {25, 27, 27, 35, 30, 28}; //in order of inlet, outlet, oxidizer, turbine1, turbine2, bleed
const int closedPositions[6] = {86, 87, 87, 97, 91, 90}; //in order of inlet, outlet, oxidizer, turbine1, turbine2, bleed

// extra PWM outputs
const int gpPWMOutput1 = 5; // extra PWM for any extra stuff

//Pyro channel initialization
const int pyro1 = 8; // pyro channel
bool pyroFiring = false; // flag to track if pyro channel is firing
unsigned long pyroStartTime = 0;

// function declarations:
void pyroCharge(unsigned long firingTime);
void openServo (PWMServo &servoName, int valveindex);
void closedServo (PWMServo &servoName, int valveindex);

//firing functions
void openFuelOutlet();
void openTurbines();
void letsBurnThisCandle();
void shutDown();
void closeFuelOutlet();
void abort();

void initializeHardware() { //system initialization
    // initalizes all servos
    mainFuelBallValve.attach(S4); 
    outletFuelBallValve.attach(S3);
    oxidizerFuelBallValve.attach(S2);
    turbine1Valve.attach(S1);
    turbine2Valve.attach(S8);
    airBleedValve.attach(S7);

    // initalizes all pins
    pinMode(gpPWMOutput1, OUTPUT);
    pinMode(pyro1, OUTPUT);

    // closes all servos in startup
    closedServo(mainFuelBallValve, 0); //closes servo 1
    closedServo(outletFuelBallValve, 1); //closes servo 2
    closedServo(oxidizerFuelBallValve, 2); //closes servo 3
    closedServo(turbine1Valve, 3); //closes servo 4
    closedServo(turbine2Valve, 4); //closes servo 5
    closedServo(airBleedValve, 5); //closes servo 6

    // ensures all PWM and Pyro outputs start LOW
    digitalWrite(gpPWMOutput1, LOW);
    digitalWrite(pyro1, LOW); // make sure pyro channel is low; critial to safety

    delay(10000); //keep this a delay as we need to make sure everything is in their positions they are meant to be in
}


// function definitions:
void pyroCharge(unsigned long firingTime) { //firing time is in milliseconds so be careful
    if (!pyroFiring) {
        digitalWrite(pyro1, HIGH); //fires pyro charge for x seconds based on time value given in firing time
        pyroStartTime = millis();
        pyroFiring = true;
        
    }

    if (pyroFiring && millis() -  pyroStartTime >= firingTime){ // if time in milliseconds is greater than or equal to firing time, it will stop the ematch
        digitalWrite(pyro1,LOW); // pin goes low; system safed
        pyroFiring = false; //resets firing flag
    }
}

void openServo (PWMServo &servoName, int valveindex) { // index goes from 0-5 (array is counting from 1-6)
    servoName.write(openPositions[valveindex]); // opens servo
} 

void closedServo (PWMServo &servoName, int valveindex) { // index goes from 0-5 (array is counting from 1-6)
    servoName.write(closedPositions[valveindex]); // closes servo
}

void openBleedValve() { // opens fuel bleed valve (purges air from system)
    openServo(airBleedValve, 5);
}

void openFuelOutlet() { // opens up fuel outlet valve as stated in procedures
    openServo(outletFuelBallValve, 1);
}

void closeBleedValve() { // closes fuel bleed valve (purges air from system)
    closedServo(airBleedValve, 5);
}

void openTurbines() { //opens up turbine valves as stated in procedures
    openServo(turbine1Valve, 3);
    openServo(turbine2Valve, 4);
}


void letsBurnThisCandle() { //opens up turbine valves as stated in procedures 
    openServo(mainFuelBallValve, 0);
    openServo(oxidizerFuelBallValve, 2);
    pyroCharge(2000);
}

void shutDown() {
    closedServo(turbine1Valve, 3);
    closedServo(turbine2Valve, 4);
    closedServo(mainFuelBallValve, 0);
    closedServo(oxidizerFuelBallValve, 2);
}

void closeFuelOutlet() {
    closedServo(outletFuelBallValve, 1);
}

void abort() {
    shutDown();
    closeFuelOutlet();
}