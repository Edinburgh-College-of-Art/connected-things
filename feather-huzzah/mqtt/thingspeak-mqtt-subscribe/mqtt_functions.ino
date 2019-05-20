void connect() 
{
  Serial.print("\nConnecting To MQTT Broker: ");
  Serial.println(broker);
  while (!client.connect("esp82866-huzzah-test-eca-1", "Username", mqttApiKey)) 
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println("\nconnected!");
  client.subscribe("channels/" + channelId + "/subscribe/fields/field"+ fieldNumber+"/"+ channelReadApiKey);
}
