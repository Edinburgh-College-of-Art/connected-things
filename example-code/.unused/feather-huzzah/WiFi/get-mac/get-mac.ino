/*
 * Get MAC Address
 */
//#include <WiFi.h>
#include <ESP8266WiFi.h>
void setup()
{
  Serial.begin(115200);
  while(!Serial){}

  Serial.println();
  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() 
{
}
