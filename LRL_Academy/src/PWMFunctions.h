#ifndef PWMFUNCTIONS_H
#define PWMFUNCTIONS_H

#include <Arduino.h>
#include <Servo.h>

// Declarations of the Servo objects and constants, but not definitions
extern Servo mainFuelBallValve;  
extern Servo outletFuelBallValve; 
extern Servo oxidizerFuelBallValve; 
extern Servo turbine1Valve; 
extern Servo turbine2Valve; 
extern Servo servoBallValveExtra1; 

extern const int openPositions[6]; // positions for open valves
extern const int closedPositions[6]; // positions for closed valves

// Declarations for extra PWM outputs
extern const int gpPWMOutput1; 
extern const int gpPWMOutput2;

// Pyro channel initialization
extern const int pyro1;
extern bool pyroFiring; // flag to track if pyro channel is firing
extern unsigned long pyroStartTime; // time when pyro started firing

// Function declarations
void pyroCharge(int firingTime);
void openServo(Servo &servoName, int valveindex);
void closedServo(Servo &servoName, int valveindex);

//firing functions
void openFuelOutlet();
void openTurbines();
void letsBurnThisCandle();
void shutDown();
void closeFuelOutlet();

#endif // PWMFUNCTIONS_H