/*
   Simple Paper Signals

   Demonstrates Chaining APIs together to get a custom output
*/
//------------------------------------------------------------------------------
#include <WiFi101.h>
#include <Servo.h>
#include <ArduinoJson.h>
//------------------------------------------------------------------------------
// API Details
const String DarkSkyAPIKey = "ENTERAPIKEY";
String weatherLocation = "Edinburgh UK";
//------------------------------------------------------------------------------
// WiFi Details
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiClient client;
WiFiSSLClient sslClient;
//------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial) {};
  connectToWifiNetwork(ssid, password);
  Serial.println("will it rain?");
  Serial.println((itIsGoingToRain(weatherLocation)) ? "yes" : "no");

}
//------------------------------------------------------------------------------
void loop()
{

  delay(5000); // look to update every 5 seconds
}
