#include <Arduino.h>
#include "PWMFunctions.h" // PWM functions

#include "SPI.h" // SPI library for teensy
#include "Ethernet.h" // Ethernet Libarary for teensy 

const int W5500_CS = 12; // pin for CS

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 100);  // Static IP
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 255, 0);

EthernetServer server(23);  // TCP server on port 23 (Telnet-style)
EthernetClient client;



void setup () {
  Serial.begin(9600);
  Serial.begin(9600);
  initializeHardware();

  // Initialize Ethernet with W5500
  Ethernet.init(W5500_CS);
  if (!Ethernet.begin(mac)) {
    Serial.println("DHCP failed, using static IP...");
    Ethernet.begin(mac, ip, gateway, gateway, subnet);
  }

  Serial.print("IP Address: ");
  Serial.println(Ethernet.localIP());

  server.begin();
  Serial.println("TCP Serial Server started");
  
}

void handleCommand(const String& cmd) {
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

void loop() {
  // Accept new client if not connected
  if (!client || !client.connected()) {
    EthernetClient newClient = server.available();
    if (newClient) {
      if (client) client.stop();  // Close previous client if needed
      client = newClient;
      client.println("Connected to Teensy TCP server.");
      Serial.println("Client connected.");
    }
  }

  // Handle incoming command
  if (client && client.connected() && client.available()) {
    String cmd = client.readStringUntil('\n');
    cmd.trim();
    cmd.toLowerCase();

    Serial.print("Command: ");
    Serial.println(cmd);

    handleCommand(cmd);
  }
}

