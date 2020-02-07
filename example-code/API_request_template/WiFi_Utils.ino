//Setting up a WiFi connection - COMPLETE

void connectToWifi(const char ssidName[], const char pass[]) 
{  
#ifdef ARDUINO_SAMD_ZERO
  WiFi.setPins(8, 7, 4, 2); // Set the WiFi pins on the Feather 
#endif

  Serial.println("Starting...");
  Serial.println("Connecting to WiFi.");

  int conn = WiFi.begin(ssidName, pass); 

  if (conn == WL_CONNECTED) 
  { 
    Serial.println("OK!");
  } 
  else if (conn == WL_IDLE_STATUS) 
  { 
    Serial.println("Idle");
  } 
  else 
  {
    Serial.println("Unknown response");
  }

}

void haltFirmware()
{
  Serial.println("STOPPING THE PROGRAM");
  while(true){}
}
