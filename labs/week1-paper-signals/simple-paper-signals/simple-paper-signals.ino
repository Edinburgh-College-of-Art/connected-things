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
const String DarkSkyAPIKey = "DARKSKYAPIKEY";
const int numberOfLocations = 3;
String weatherLocation[numberOfLocations] = {"Edinburgh UK", "London UK", "Tokyo"};
//------------------------------------------------------------------------------
// WiFi Details
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiClient client;
WiFiSSLClient sslClient;
//------------------------------------------------------------------------------
Servo myservo;
void servoFunction(bool val)
{
  myservo.write((val) ? 0 : 90);
}
//------------------------------------------------------------------------------
void setup()
{
  myservo.attach(9);
  Serial.begin(9600);
  while (!Serial) {};
  connectToWifiNetwork(ssid, password);
}
//------------------------------------------------------------------------------
void loop()
{
  for (int i = 0; i < numberOfLocations; i++)
  {
    Serial.println("will it rain in:");
    Serial.println(weatherLocation[i] + "?");
    servoFunction(itIsGoingToRain(weatherLocation[i]));
    delay(2000);
  }
  delay(5000); // look to update every 5 seconds
}
