#include <Arduino.h>
#include <Servo.h>
#include <PWMOutput.h>

//servo outputs
Servo servoBallValve1; // valve 1
Servo servoBallValve2; // valve 2
Servo servoBallValve3; //valve 3
Servo servoBallValve4; //valve 4
Servo servoBallValveExtra1; // extra servo output
Servo servoBallValveExtra2; // extra servo output
const int openPositions[6] = {180, 180, 180, 180, 180, 180}; // goes in order of servoBallValve1, servoBallValve2, servoBallValve3, servoBallValve4, servoBallValveExtra1, servoBallValveExtra2
const int closedPositions[6] = {0, 0, 0, 0, 0, 0}; // goes in order of servoBallValve1, servoBallValve2, servoBallValve3, servoBallValve4, servoBallValveExtra1, servoBallValveExtra2

// extra PWM outputs
const int gpPWMOutput1 = 36; // extra PWM for any extra stuff
const int gpPWMOutput2 = 33; // extra PWM for any extra stuff

//Pyro channel initialization
const int pyro1 = 28; // pyro channel
bool pyroFiring = false; // flag to track if pyro channel is firing
unsigned long pyroStartTime = 0;

// function declarations:
void pyroCharge(int firingTime);
void openServo (Servo &servoName, int valveindex);
void closedServo (Servo &servoName, int valveindex);


void setup() {
    // initalizes all servos
    servoBallValve1.attach(11); 
    servoBallValve2.attach(24);
    servoBallValve3.attach(25);
    servoBallValve4.attach(29);
    servoBallValveExtra1.attach(14);
    servoBallValveExtra2.attach(37);

    // initalizes all pins
    pinMode(gpPWMOutput1, OUTPUT);
    pinMode(gpPWMOutput2, OUTPUT);
    pinMode(pyro1, OUTPUT);

    // closes all servos in startup
    closedServo(servoBallValve1, 0); //closes servo 1
    closedServo(servoBallValve2, 1); //closes servo 2
    closedServo(servoBallValve3, 2); //closes servo 3
    closedServo(servoBallValve4, 3); //closes servo 4
    closedServo(servoBallValveExtra1, 4); //closes servo 5
    closedServo(servoBallValveExtra2, 5); //closes servo 6

    // ensures all PWM and Pyro outputs start LOW
    digitalWrite(gpPWMOutput1, LOW);
    digitalWrite(gpPWMOutput2, LOW);
    digitalWrite(pyro1, LOW); // make sure pyro channel is low; critial to safety

    delay(5000);
}

void loop() {
  // nothing I need to add
}

// function definitions:
void pyroCharge(int firingTime) { //firing time is in milliseconds so be careful
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

void openServo (Servo &servoName, int valveindex) { // index goes from 0-5 (array is counting from 1-6)
    servoName.write(openPositions[valveindex]); // opens servo
} 

void closedServo(Servo &servoName, int valveindex) { // index goes from 0-5 (array is counting from 1-6)
    servoName.write(closedPositions[valveindex]); // closes servo
}
