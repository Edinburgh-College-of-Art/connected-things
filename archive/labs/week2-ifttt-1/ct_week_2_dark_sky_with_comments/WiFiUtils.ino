void connectToWifi(const char ssidName[], const char pass[])
{
  Serial.begin(9600); // open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // wait until the Serial port is open

  WiFi.setPins(8, 7, 4, 2); // Set the WiFi pins on the Feather – you can skip this step if using the IoT 33 Nano

  Serial.println("Starting..."); // Print a message to the Serial so you can monitor what's going on
  Serial.println("Connecting to WiFi.");

  int conn = WiFi.begin(ssidName, pass); // connect to the WiFi network, passing in the values for the network name and password

  if (conn == WL_CONNECTED)  // Check if you have successfully connected to the WiFi network
  {
    Serial.println("OK!"); // If connected print a confirmation message to the Serial
  }
  else if (conn == WL_IDLE_STATUS)  // If you've not connected successfully print an error message
  {
    Serial.println("Idle");
  }
  else
  {
    Serial.println("Unknown response");
  }

}
