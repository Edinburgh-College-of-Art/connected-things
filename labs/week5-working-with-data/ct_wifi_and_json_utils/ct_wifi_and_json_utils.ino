// This sketch is a template for making calls to an API and downloading data in JSON format 

#include <WiFiNINA.h> // Use this library if you are using an Arduino Nano 33 IoT
// #include <WiFi101.h> // Use this library if you are using a Feather M0
#include <ArduinoJson.h>

// WiFi Network ------------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the name of your local WiFi Network
const char* password = "your_password"; // Replace with the password for your local WiFi Network

// WiFi Clients ------------------------------------------------------
WiFiClient client; // a client for unsecure connections
WiFiSSLClient sslClient; // a client for secure connections

void setup() {

  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while(!Serial) {} // Do nothing until the Serial port is ready

  connectToWiFi(ssid, password); // Connect to WiFi

}

void loop() {
  // put your main code here, to run repeatedly:

}
