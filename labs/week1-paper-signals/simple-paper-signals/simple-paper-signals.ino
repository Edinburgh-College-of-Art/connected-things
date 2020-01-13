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
String weatherLocation[] = {"Edinburgh UK", "London UK", "Tokyo"};
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
  
  for (int i = 0; i < 3; i++)
  {
    Serial.println("will it rain in:");
    Serial.println(weatherLocation[i] + "?");
    servoFunction(itIsGoingToRain(weatherLocation[i]));
    delay(2000);
  }

}
//------------------------------------------------------------------------------
void loop()
{

  delay(5000); // look to update every 5 seconds
}
