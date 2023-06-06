/*
  ThingSpeakSetup

  This Example will send a random number betyween 0 to 1000 to a specified number of fields.

  Pay attention to Serial Output for information about your WiFi Card

*/
//================================================================================
#include <ThingSpeak.h>
#include <SPI.h>
#include <WiFi101.h>
//================================================================================
const char ssid[] = "ssid";
const char password[] = "password";   // your network password
WiFiClient  client;
//================================================================================
unsigned long myChannelNumber = 123456;          //Put your channel number in here
const char * myWriteAPIKey = "123456789ABCDEFG"; //Put your API key in here
//================================================================================
// Data vairables

uint8_t fields = 2; // number of fields in channel

//================================================================================
void setup()
{
  connectToWifiNetwork(ssid, password);
  ThingSpeak.begin(client); // Now connect to ThingSpeak
  Serial.println("Started");
  randomSeed(analogRead(0)); // Seed the random number generator
}

//================================================================================

void loop()
{
  for (int i = 0; i < fields; ++i)
  {
    int randomNumber = random(1000);
    Serial.print(randomNumber); Serial.print(" ");
    ThingSpeak.setField(i, randomNumber);
  }
  Serial.println();

  int resp = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  Serial.print("Response: ");
  Serial.println(resp);

  delay(20000); // ThingSpeak will only accept updates every 15 seconds.
}
