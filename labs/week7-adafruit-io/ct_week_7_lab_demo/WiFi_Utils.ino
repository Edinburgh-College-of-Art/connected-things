// The code on this tab is only used to connect your Arduino to the local WiFi network
// You can re-use it in all your programs without changing anything

void connectToWiFi(const char ssidName [], const char pass []) {

  Serial.println("Starting..."); 
  Serial.println("Connecting to WiFi.");

  // WiFi.setPins(8, 7, 4, 2); // Uncomment this line if you are using the Feather M0

  int conn = WiFi.begin(ssidName, pass); 
  
  if (conn == WL_CONNECTED) { 
    Serial.println("OK!"); 
  } else if (conn == WL_IDLE_STATUS) {
    Serial.println("Idle.");
  } else {
    Serial.println("Unknown response.");
  }

} // End of connectToWiFi
