// The code on this tab is general code for connecting your Arduino Nano IoT 33 to WiFi
// You can re-use it in your program without changing anything

void connectToWiFi(const char ssidName [], const char pass []) { // The values you pass in here are the name and password for your local WiFi network

  Serial.println("Starting..."); // Print a message to the Serial port so you can check what's going on
  Serial.println("Connecting to WiFi.");

  int conn = WiFi.begin(ssidName, pass); // connect to the WiFi network, passing in the network name and password 

  if (conn == WL_CONNECTED) { // Check if you have successfully connected to WiFi
    Serial.println("OK!"); // If you have, print a confirmation message to the Serial port
  } else if (conn == WL_IDLE_STATUS) { // If not print an error message
    Serial.println("Idle.");
  } else {
    Serial.println("Unknown response.");
  }


}
