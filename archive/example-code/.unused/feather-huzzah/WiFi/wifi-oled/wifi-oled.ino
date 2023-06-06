/*
    Simple HTTP get webclient test
*/
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//----------------------------------------------------------------
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
//----------------------------------------------------------------
const char* ssid     = "HANABI";
const char* password = "hanabi_password";
const char* host = "wifitest.adafruit.com";
//----------------------------------------------------------------
void setup()
{
  Serial.begin(115200);
  setupOLED();
  delay(100);
  while (!Serial) {} // wait for Serial Monitor
  connectToWifi(ssid, password);
  showWifiDetails();
}
//----------------------------------------------------------------
void loop()
{
  delay(5000);
  connectToHost(host);
}
