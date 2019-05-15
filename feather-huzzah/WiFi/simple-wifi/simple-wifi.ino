/*
    Simple HTTP get webclient test
*/
#include <ESP8266WiFi.h>
//----------------------------------------------------------------
const char* ssid     = "yourssid";
const char* password = "yourpassword";
const char* host = "wifitest.adafruit.com";
//----------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  delay(100);
  while (!Serial) {} // wait for Serial Monitor
  connectToWifi(ssid, password);
}
//----------------------------------------------------------------
void loop()
{
  delay(5000);
  connectToHost(host);
}
