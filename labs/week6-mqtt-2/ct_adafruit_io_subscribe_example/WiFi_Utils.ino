// The code on this tab is only used to connect your Arduino to the local WiFi network
// You can re-use it in all your programs without changing anything

void connectToWiFi(const char ssidName [], const char pass [])
{
  // The values you pass into this function are the name and password for your local WiFi network

  Serial.println("Starting..."); // Print a message to the Serial port so you can keep an eye on what's going on
  Serial.println("Connecting to WiFi.");

  // WiFi.setPins(8, 7, 4, 2); // Uncomment this line if you are using the Feather M0

  int conn = WiFi.begin(ssidName, pass); // Connect to WiFi, passing in the network name and password
  // The int "conn" here is the status code returned when the Arduino tries to connect to WiFi

  if (conn == WL_CONNECTED)  // Check if you have successfully connected to WiFi
  {
    Serial.println("OK!"); // If you have, print a confirmation message to the Serial
  }
  else if (conn == WL_IDLE_STATUS)  // If not, then print an error message to the Serial
  {
    Serial.println("Idle.");
  }
  else {
    Serial.println("Unknown response.");
  }

} // End of connectToWiFi
