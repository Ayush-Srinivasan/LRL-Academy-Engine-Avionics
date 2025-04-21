#include <Arduino.h>
#include "PWMFunctions.h" //PWM functions

#include "QNEthernet.h" //ethernet library for teensy
using namespace qindesign::network;

EthernetServer server(23);  // Port 23 = Telnet-style serial

void setup () {
  Serial.begin(9600);
  initializeHardware();

  if (!Ethernet.begin()) {
    Serial.println("Ethernet failed to start");
    while (true);
  }

    Serial.print("IP Address: ");
    Serial.println(Ethernet.localIP());

    server.begin();
    Serial.println("TCP Serial Server started");
  
}

void loop() {
  EthernetClient client = server.available();

  if (client && client.connected()) {
    if (client.available()) {
      String cmd = client.readStringUntil('\n');
      cmd.trim();
      cmd.toLowerCase();

      Serial.print("Command: ");
      Serial.println(cmd);

      if (cmd == "o") {
        openFuelOutlet();
        client.println("Opened fuel outlet.");
      } else if (cmd == "b") {
        openBleedValve();
        client.println("Opened bleed valve.");
      } else if (cmd == "t") {
        openTurbines();
        client.println("Opened turbines.");
      } else if (cmd == "v") {
        closeBleedValve();
        client.println("Closed bleed valve.");
      } else if (cmd == "f") {
        letsBurnThisCandle();
        client.println("Firing sequence triggered.");
      } else if (cmd == "s") {
        shutDown();
        client.println("Shutdown complete.");
      } else if (cmd == "c") {
        closeFuelOutlet();
        client.println("Closed fuel outlet.");
      } else if (cmd == "a") {
        abort();
        client.println("ABORT!");
      } else if (cmd == "?") {
        client.println("Commands:");
        client.println("  o = open fuel outlet");
        client.println("  b = open bleed valve");
        client.println("  t = open turbines");
        client.println("  v = close bleed valve");
        client.println("  f = fire");
        client.println("  s = shutdown");
        client.println("  c = close fuel outlet");
        client.println("  a = abort");
      } else {
        client.println("Unknown command.");
      }
    }
  }
}


