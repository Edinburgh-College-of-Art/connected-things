/**
 Connects adafruit feather M0 to ECA hanabi network

 Contact Matthew for the password.

 @param pass network password
 @return returns the connection status for transparent error checking.
 
 */
void connectToWifiNetwork(const char ssidName[],const char pass[])
{
 Serial.begin(9600);   // Make sure that the number in the bottom right of the Serial Monitor matches this
  while( !Serial) {}    // Wait until the Serial port is ready so we don't miss any output
  WiFi.setPins(8,7,4,2); // Setup the WiFi on the Feather boards

  /* Start the WiFi connection */
  Serial.println("Starting..."); 
  Serial.println("Connecting to WiFi");  
  int conn = WiFi.begin(ssidName, pass);
  if( conn == WL_CONNECTED )        { Serial.println("OK!");}
  else if( conn == WL_IDLE_STATUS ) {Serial.println("Idle");}
  else                              {Serial.println("Unknown response");}
}
