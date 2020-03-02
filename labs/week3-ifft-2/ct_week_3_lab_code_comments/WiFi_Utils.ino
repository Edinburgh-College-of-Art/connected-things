void connectToWiFi(const char ssidName [], const char pass[]) {

  Serial.begin(9600); // open the Serial port and set the baud rate (communication speed)
  while (!Serial) {} // wait until the Serial port is open

  WiFi.setPins(8, 7, 4, 2); // you can skip this step if using the IoT 33 Nano instead of a Feather

  Serial.println("Starting..."); // print a message to the Serial so you can monitor what's going on
  Serial.println("Connecting to WiFi Network.");

  int conn = WiFi.begin(ssidName, pass); // connect to the WiFi network

  if (conn == WL_CONNECTED) { // check if you've successfully connected to the WiFi network
    Serial.println("OK!"); // if connected print a confirmation message to the Serial
  } else if (conn == WL_IDLE_STATUS) { // if you've not connected sucessfully print an error message
    Serial.println("Idle.");
  } else {
    Serial.println("Unknown Response.");
  }

}
