// This sketch demonstrates how to send values to a Google Sheets spreadsheet using IFTTT
// Remember you will need to set up you own IFTTT applet on the website and connect your Google account

// The first thing you need to do is import the WiFi library for your Arduino
// For the Feather M0 you need WiFi101
// For the Arduino Nano IoT 33 in your kit you need WiFiNINA - add this by going to Tools > Manage Libraries

// Libraries ---------------------------
#include <WiFi101.h> // for the Feather M0
// #include <WiFiNINA.h> // for the Nano IoT 33

// WiFi Network ------------------------
const char* ssid = "HANABI"; // If you are not at ECA, replace this with your local WiFi network name and password
const char* password = "lowernorwood";

// IFTTT -------------------------------
WiFiClient client; // Create a new WiFiClient – this is an unsecured connection (Port 80)

// Setup -------------------------------
void setup()  // runs once
{// Call the function that connects you to the WiFi network (on WiFi_Utils tab), passing in the values for ssid and password
  connectToWiFi(ssid, password);

  int v1 = int(random(500)); // generate a random integer (whole number) between 0 and 500
  int v2 = int(random(500)); // remember these could also be readings from sensors attached to your Arduino
  int v3 = int(random(500));

  // Call the function that sends the HTTP GET Request to IFTTT (on IFTTT tab), passing in the values that you generated above
  connectToIFTTT(v1, v2, v3);
}
// Loop ---------------------------------
void loop()  // runs continuously
{// I'm not using the loop in this example – but whatever you do, do not just paste your connectToIFTTT function in here as you will quickly exceed your rate limit!
}
