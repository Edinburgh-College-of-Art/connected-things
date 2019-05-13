/*
   WiFi Web Server LED Blink: Blink an LED via the web.
*/
//========================================================================
#include <SPI.h>
#include <WiFi101.h>
//========================================================================
char ssid[] = "Feather Wifi Server";
char pass[] = "feather";
IPAddress ipAddress = IPAddress(10, 0, 0, 1);
//========================================================================
int status = WL_IDLE_STATUS;
WiFiServer server(80);
//========================================================================
void setup()
{ 
  //  connectToWifiNetwork(ssid, pass);
  setAccessPoint(ssid, ipAddress);
  printWiFiStatus();
}
//========================================================================
void loop()
{
  reportConnection();
  deliverWebsite();
}
//========================================================================

void errorProtocol()
{
  while (true)
  {
    // do something if there is a problem
  }
}
