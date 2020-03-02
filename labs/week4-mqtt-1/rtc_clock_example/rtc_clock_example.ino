// This example demonstrates how to set the Arduino Nano IoT 33's Real Time Clock, by requesting the current time from the the World Time API
// This is useful if you want to program your Arduino to do something (e.g. download data, reset the value of a variable, turn an LED on) at a particular time of day
// You can also find a useful tutorial here: https://itp.nyu.edu/physcomp/labs/lab-using-a-real-time-clock/

// Import the Libraries for WiFi, JSON, and Real Time Clock
#include <WiFiNINA.h>
#include <ArduinoJson.h>
#include <RTCZero.h> // You will need to download the RTCZero library using the Arduino Libraries manager

// WiFi ----------------------------------
const char* ssid = "your_ssid"; // replace these with the name and password for your local WiFi network
const char* password = "your_password";

// Clients -------------------------------
WiFiClient client; // create a new WiFi client so you can communicate with the server

// RTC ----------------------------------
RTCZero rtc; // create a new RTCZero object and give it a name


// Setup --------------------------------
void setup() {

  Serial.begin(9600); // Open the Serial port
  while (!Serial) {} // Do nothing until the Serial port is ready

  connectToWiFi(ssid, password); // connect to the WiFi network

  setRTC(); // call the function to set the real time clock (on RTC tab) 

  int h = rtc.getHours(); // Use this to check the clock is set correctly 
  int m = rtc.getMinutes();

  Serial.println("Time from Clock: " + String(h) + ":" + String(m)); // Print the curren time to the Serial port

}


// Loop ---------------------------------
void loop() {

  // not used in this example

}
