void connectToMqtt(const char clientId[])
{
  // You can provide a unique client ID, if not set the library uses Arduino-millis()
  // Each client must have a unique client ID
  // mqttClient.setId("clientId");
  if (clientId)
  {
    mqttClient.setId(clientId);
  }
  mqttClient.setUsernamePassword("Username", mqttApiKey);

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port))
  {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());
    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

}

void connectToMqtt()
{
  connectToMqtt(nullptr);
}
