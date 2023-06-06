/*
 * Feather M0: Thing Speak Manual
 * 
 * Manually cook up a REST request for talking to thingspeak.
 * 
 * Send 2 random numbers to ThingSpeak with an Adafruit Feather M0 with WiFi
 * every 15 seconds 
 */
//==============================================================================
#include <SPI.h>
#include <WiFi101.h>
//==============================================================================
String APIkey = "123456789ABCDEFG"; // Use your own API WRITE key here!
const uint8_t fields = 2;           // number of thing speak fields
uint32_t data[fields]  = {0};       // The data is an integer
//==============================================================================
WiFiClient thingSpeakClient;
int connectionsPosted = 0;
const char ssid[] = "ssid";
const char *password = "hanabi-password";
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  connectToWifiNetwork(ssid, password);
  randomSeed(analogRead(0)); // Seed the random number generator
  Serial.println(thingSpeakClient.connected());
}

//==============================================================================

void loop()
{
  String dataAsString[fields];
  for (int i = 0; i < fields; ++i)
  {
    data[i] = random(300);
    dataAsString[i] = data[i];
  }
  sendDataToThingSpeak(dataAsString, fields, APIkey, thingSpeakClient);
  ++connectionsPosted;
  Serial.print("Connections Posted: ");
  Serial.println(connectionsPosted);
  delay(25000);
}

//===========================================================================
