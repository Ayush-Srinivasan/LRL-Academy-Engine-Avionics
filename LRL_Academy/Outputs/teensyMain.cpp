#include <Arduino.h>
#include <PWMFunctions.h> //PWM functions
//#include <QNEthernet.h> //ethernet library teensy
//#include <QNEthernet.h>


void setup () {
  Serial.begin(9600);
  initializeHardware();
}

void loop () {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim(); // Remove any extra whitespace or newline

    if (command == "fire") {
      pyroCharge(5000);
      Serial.println("pyro1 firing");
    } 
    else if (command == "servo_on") {
      openFuelOutlet();
      Serial.println("Outlet Fuel Ball Valve Open");
    } 
    else {
      Serial.println("Unknown command");
    }
  }
}