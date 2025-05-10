#ifndef PWMFUNCTIONS_H
#define PWMFUNCTIONS_H

#include <Arduino.h>
#include <PWMServo.h>


// Declarations of the Servo objects and constants, but not definitions
extern PWMServo mainFuelBallValve;  
extern PWMServo outletFuelBallValve; 
extern PWMServo oxidizerFuelBallValve; 
extern PWMServo turbine1Valve; 
extern PWMServo airBleedValve; 

extern const int openPositions[6]; // positions for open valves
extern const int closedPositions[6]; // positions for closed valves

// Declarations for extra PWM outputs
extern const int gpPWMOutput1; 

// Pyro channel initialization
void initializeHardware();
extern const int pyro1;
extern bool pyroFiring; // flag to track if pyro channel is firing
extern unsigned long pyroStartTime; // time when pyro started firing

// Function declarations
void pyroCharge(unsigned long firingTime);
void openServo(PWMServo &servoName, int valveindex);
void closedServo(PWMServo &servoName, int valveindex);

//firing functions
void openBleedValve();
void closeBleedValve();
void openFuelOutlet();
void openTurbines();
void letsBurnThisCandle();
void shutDown();
void closeFuelOutlet();
void emergencyAbort();

#endif // PWMFUNCTIONS_H