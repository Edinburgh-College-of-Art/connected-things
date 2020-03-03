// This example demonstrates how to download JSON data from an API
// It uses Dark Sky as an example, but the general structure of the code can be adapted for other APIs

// Libraries -------------------------
// First import the right WiFi library for your Arduino
#include <WiFiNINA.h> // use this for the Nano 33 IoT board
//#include <WiFi101.h> // use this for the Feather M0
#include <ArduinoJson.h> // import the Arduino Json library

// WiFi Network ----------------------
const char* ssid = "your_ssid"; // replace with the values for your local WiFi network
const char* password = "your_password";

// WiFi Client -----------------------
WiFiSSLClient client; // create a new WiFiSSLClient – this is to allow you to create a secure connection to the API


// SETUP -----------------------------
void setup()
{
  Serial.begin(9600); // open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // do nothing until the Serial port is open

  connectToWiFi(ssid, password); // connect to WiFi
  checkWeather(); // call the checkWeather function to get a weather forecast from Dark Sky (on checkWeather tab)

}
// LOOP -------------------------------
void loop()  // Not used in this example
{// put your main code here, to run repeatedly:
}
