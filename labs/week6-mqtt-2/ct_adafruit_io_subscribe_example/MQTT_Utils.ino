// The code on this tab is only used to connect your Arduino to Adafruit IO via MQTT
// You can re-use it in all your programs without changing anything

void connectToMQTT()
{

  int8_t ret; // Create an signed int (8 bytes) to hold the status code returned by the Adafruit IO server

  if (mqtt.connected())  // If MQTT is already connected, Arduino will return to the main loop and not execute any of the code below
  {
    return;
  }

  Serial.println("Connecting to MQTT..."); // Print a message to the Serial port so you can see what is going on

  uint8_t retries = 3; // Create an unsigned int to hold the maximum number of attempts Arduino will make to connect to MQTT
  // If the Arduino cannot connect after 3 tries – it will give up and do nothing until it is manually reset

  // If the Arduino has successfully connected to Adafruit IO, the status code returned will be 0
  while ((ret = mqtt.connect()) != 0)  // If the Arduino has not successfully connected (i.e. the return code does not equal 0)
  {
    Serial.println(mqtt.connectErrorString(ret)); // Print an error message to the Serial
    Serial.println("Retrying MQTT connection in 5 seconds..."); // Print a retry message to the Serial – so you can keep an eye on what's going on
    mqtt.disconnect(); // Disconnect from MQTT
    delay(5000); // Wait for 5 seconds
    retries--;// Reduce the value of retries by 1 (-- means subtract one)
    if (retries == 0)  // If you have run out of retries...
    {
      while (1)
        ; // ...do nothing until the Arduino is manually reset.
    }
  }

  // In the above code while(1) basicallly creates an infinite loop – it is always true so the Arduino cannot execute any other code.
  // The only way to break it is to manually reset the Arduino.
  // For more info, see this forum post: https://forum.arduino.cc/index.php?topic=361516.0

  Serial.println("MQTT Connected!"); // If we have connected to Adafruit IO sucessfully, print a success message to the Serial port.

} // End of connectToMQTT
