#ifndef PWMOUTPUT_H
#define PWMOUTPUT_H

#include <Arduino.h>
#include <Servo.h>

// Declarations of the Servo objects and constants, but not definitions
extern Servo servoBallValve1; 
extern Servo servoBallValve2; 
extern Servo servoBallValve3;
extern Servo servoBallValve4;
extern Servo servoBallValveExtra1;
extern Servo servoBallValveExtra2;

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

#endif // PWMOUTPUT_H