/*
   Simple MQTT Subscribe: Arduino MQTT Client Library
*/
//---------------------------------------------------------
#include <ArduinoMqttClient.h>
#include <ESP8266WiFi.h>
//---------------------------------------------------------
// Wifi
WiFiClient wifiClient;
const char ssid[] = "HANABI";
const char pass[] = "hanabi_password";
//---------------------------------------------------------
// Thing Speak
MqttClient mqttClient(wifiClient);
const char broker[] = "mqtt.thingspeak.com";
const int port = 1883;
const char mqttApiKey[] = "0123456789ABCDEF";
const char topic[]  = "channels/<channelID>/subscribe/fields/field<fieldNumber>/<readApiKey>";
//---------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}
  connectToWifi(ssid, pass);
  //-------------------------------------------------------
  connectToMqtt();
  //-------------------------------------------------------
  mqttClient.onMessage(onMqttMessage); // set the message receive callback
  Serial.print("Subscribing to topic: ");
  Serial.println(topic);  
  mqttClient.subscribe(topic);   // subscribe to a topic
  //-------------------------------------------------------
}
//---------------------------------------------------------
void loop()
{
  mqttClient.poll(); // avoids being disconnected by the broker
  yield();
}

void onMqttMessage(int messageSize)
{
  Serial.print("\n\n\nReceived a message with topic '");
  Serial.print(mqttClient.messageTopic());
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");
  while (mqttClient.available())
  {
    Serial.print((char)mqttClient.read());
  }
}
