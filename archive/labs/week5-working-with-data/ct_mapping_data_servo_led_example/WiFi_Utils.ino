// The code on this tab is general code for connecting your Arduino to WiFi
// You can re-use it in all your programs without changing anything

void connectToWiFi(const char ssidName [], const char pass [])  // The values you pass in here are the name and passoword for your local WiFi network
{
  Serial.println("Starting..."); // Print a message to the Serial so you can monitor what's going on
  Serial.println("Connecting to WiFi Network.");

  //WiFi.setPins(8, 7, 4, 2); // This line sets the pins on the Feather M0 – uncomment this line if you are using the Arduino Nano 33 IoT

  int conn = WiFi.begin(ssidName, pass); // connect to the WiFi network, passing in the network name and password
  // The int conn here is the status code returned when the Arduino tries to connect to WiFi

  if (conn == WL_CONNECTED)  // Check if you have successfully connected to WiFi
  {
    Serial.println("OK!"); // If you have, print a confirmation message to the Serial
  }
  else if (conn == WL_IDLE_STATUS)  // If not, then print an error message to the Serial
  {
    Serial.println("Idle.");
  }
  else
  {
    Serial.println("Unknown Response.");
  }

}
