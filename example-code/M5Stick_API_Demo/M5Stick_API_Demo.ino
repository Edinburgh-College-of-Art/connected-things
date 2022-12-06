#include <M5StickCPlus.h>
#include <WiFi.h>
#include <Arduino_JSON.h>
#include "esp32-hal-ledc.h"
//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Connection
const char* ssid = "Matthew"; 
const char* pass = "arch_ma_arduino";
//---------------------------------------------------------------------------------------------------------------------------------------
WiFiClient client;
//---------------------------------------------------------------------------------------------------------------------------------------
void setup() {
  M5.begin(); 
  Serial.begin(115200);
  setupDisplay();
  connectToWiFi();
  setupServo();
}

void loop() {  
  float degCelcius = getTodaysTemperatureAtHour(15);
  int deg = int(degCelcius * 10.0);
  Serial.println(deg);
  setServoToPosition(deg);
  delay(10000);
}
