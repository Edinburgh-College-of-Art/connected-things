/*
  Send IFTTT Webhook POST request
*/
#include <WiFi101.h>
#include <EEPROM.h>
//====================================================================
const char ssid[] = "SSID";
const char password[] = "PASSWORD";   // your network password
WiFiClient  client;
//====================================================================
char MakerIFTTT_Key[]   = "123456789ABCDEF1234567";                         
char MakerIFTTT_Event[] = "send_data";
//====================================================================
const byte dataPin  = A0;
byte triggerPin = 4;
const unsigned long loopDelay = (120 * 1000);
//====================================================================
void setup() 
{
  connectToWifiNetwork(ssid, password);
  pinMode(dataPin, INPUT_PULLUP);    
  pinMode(triggerPin, INPUT_PULLUP);
}
//====================================================================
void loop() 
{  
  if (digitalRead(triggerPin) == HIGH) 
  {
    update_event(analogRead(dataPin));   // read the pins, send to IFTTT/Maker    
    delay(loopDelay);
  }
}
//====================================================================
