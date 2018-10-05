/*
  Ping Test

  Ping a website and wait for a response
 
*/
//==============================================================================
#include <SPI.h>
#include <WiFi101.h>
//==============================================================================
const char ssid[] = "SSID";
const char password[] = "PASSWORD";   // your network password
WiFiClient  client; 
//==============================================================================
String hostName = "www.google.com";
int pingResult;
//==============================================================================
void setup() 
{
  connectToWifiNetwork(ssid,password);
}

//==============================================================================

void loop() 
{
  /* Now, test the wifi connection by trying to connect to a server that we know works */
  Serial.print("Pinging ");
  Serial.print(hostName);
  Serial.print(": ");
  pingResult = WiFi.ping(hostName);

  if (pingResult >= 0) {
    Serial.print("SUCCESS! RTT = ");
    Serial.print(pingResult);
    Serial.println(" ms");
  } else {
    Serial.print("FAILED! Error code: ");
    Serial.println(pingResult);
  }

  delay(2000); // Wait...

}
