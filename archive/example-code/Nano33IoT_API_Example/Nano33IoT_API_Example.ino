#include <WiFiNINA.h>
#include <Servo.h>
#include <Arduino_JSON.h>
#include <ArduinoJson.h>
//------------------------------------------------------------------------------
// WiFi Connection
const char* ssid = "Matthew";
const char* pass = "arch_ma_arduino";
//------------------------------------------------------------------------------
WiFiClient client;
//------------------------------------------------------------------------------
Servo servo;
const int servoPin = 3;
//------------------------------------------------------------------------------
void setup() 
{
  Serial.begin(115200);
  connectToWiFi();
  setupServo();
}
//------------------------------------------------------------------------------
void loop() 
{
  float degCelcius = getTodaysTemperatureAtHour(15);
  int deg = int(degCelcius * 10.0);
  Serial.println(deg);
  setServoToPosition(deg);
  delay(10000);
}
