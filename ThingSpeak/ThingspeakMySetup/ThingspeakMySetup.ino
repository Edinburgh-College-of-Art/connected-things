/*
  ThingSpeakSetup
  
  Reads an analog voltage from pin 0, and writes it to a channel on ThingSpeak every 20 seconds.


   Visit https://www.thingspeak.com to sign up for a free account and create
  a channel.  The video tutorial http://community.thingspeak.com/tutorials/thingspeak-channels/ 
  has more information. You need to change this to your channel, and your write API key
  
  IF YOU SHARE YOUR CODE WITH OTHERS, MAKE SURE YOU REMOVE YOUR WRITE API KEY!!
  
*/
//================================================================================
#include "ThingSpeak.h"
#include <SPI.h>
#include <WiFi101.h>
//================================================================================
char password[] = "PASSWORD";   // your network password
WiFiClient  client; 
//================================================================================
unsigned long myChannelNumber = 0; //Put your channel number in here
const char * myWriteAPIKey = "ABCDEFGHIJKLMNOP"; //Put your API key in here
//================================================================================

void setup() 
{
  connectToHanabi(password);
  /* Now connect to ThingSpeak */
  ThingSpeak.begin(client);
  Serial.println("Started");
}
//================================================================================
void loop() 
{  
  int sensorValue = analogRead(A5);
  float voltage = sensorValue * (3.3 / 1024.0); //The voltage can be between 0 and 3.3v, and gives readings from 0 to 2013
  
  ThingSpeak.setField(1,(float)analogRead(A5));
  //ThingSpeak.setField(2,(float)analogRead(A0));
  int resp = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  //int resp = ThingSpeak.writeField(myChannelNumber, 1, voltage, myWriteAPIKey);
  Serial.print("Response: ");
  Serial.println(resp);
  delay(2000); // ThingSpeak will only accept updates every 15 seconds.
}
