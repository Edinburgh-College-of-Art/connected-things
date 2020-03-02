// The code on this tab is only used to connect your Arduino to Adafruit IO via MQTT
// You can re-use it in all your programs without changing anything

void connectToMQTT() {

  int8_t ret;

  if (mqtt.connected()) {
    return;
  }

  Serial.println("Connecting to MQTT...");

  uint8_t retries = 3;

  while ((ret = mqtt.connect()) != 0) {
    Serial.println(mqtt.connectErrorString(ret));
    Serial.println("Retrying MQTT connection in 5 seconds...");
    mqtt.disconnect();
    delay(5000);
    retries --;
    if (retries == 0) {
      while (1);
    }
  }

  Serial.println("MQTT Connected!");

} // End of connectToMQTT
