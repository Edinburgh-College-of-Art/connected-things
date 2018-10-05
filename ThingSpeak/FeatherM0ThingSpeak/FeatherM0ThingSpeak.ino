//==============================================================================
// Feather M0: Thing Speak
//
//  Send 2 random numbers to ThingSpeak with an Adafruit Feather M0 with WiFi
// every 15 seconds
//==============================================================================
#include <SPI.h>
#include <WiFi101.h>
#include "ecaWifiUilities.h"
#include "talkToThingSpeak.h"
//==============================================================================
String APIkey = "ABCDEFGHIJKLMNOP"; // Use your own API WRITE key here!
const uint8_t fields = 2;           // number of thing speak fields
uint32_t data[fields]  = {0};       // The data is an integer
//==============================================================================
void setup()
{
  Serial.begin(9600);
  while (!Serial) {} // This is required with the M0 due to a bug
  connectToHanabi("HANABI_PASSWORD");
  randomSeed(analogRead(0)); // Seed the random number generator
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
  sendDataToThingSpeak(dataAsString, fields, APIkey);
  delay(15000);
}

//===========================================================================

