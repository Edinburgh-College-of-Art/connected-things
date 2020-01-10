/*
 * ThingSpeak MQTT: read the first field of an MQTT channel
 */
//---------------------------------------------------------
#include <ESP8266WiFi.h>
#include <MQTT.h> // by Joël Gähwiler
//---------------------------------------------------------
// Wifi
WiFiClient wifiClient;
const char ssid[] = "HANABI";
const char pass[] = "hanabi_password";
//---------------------------------------------------------
// Thing Speak
MQTTClient client;
const char broker[] = "mqtt.thingspeak.com";
const char mqttApiKey[]  = "0123456789ABCDEF";
String channelReadApiKey = "0123456789ABCDEF";
String channelId = "629081";
String fieldNumber = "1";
//---------------------------------------------------------
unsigned long lastMillis = 0;
//---------------------------------------------------------
void doThisWhenMessageReceieved(String &topic, String &payload)
{
  Serial.println("incoming: " + topic + " - " + payload);
}
//---------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  connectToWifi(ssid, pass);
  client.begin(broker, wifiClient);
  client.onMessage(doThisWhenMessageReceieved);
  connect();
}
//---------------------------------------------------------
void loop()
{
  client.loop();  
  if (!client.connected())
  {
    connect();
  }
  yield();// <- fixes some issues with WiFi stability
}
