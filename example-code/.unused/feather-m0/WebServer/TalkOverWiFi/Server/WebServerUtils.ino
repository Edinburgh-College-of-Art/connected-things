//========================================================================

void setAccessPoint(const char ssidName[], int keyIndex, const char password[], IPAddress ip)
{
  Serial.begin(9600);
  while (!Serial) {};
  WiFi.setPins(8, 7, 4, 2); // Setup the WiFi on the Feather boards
  checkFirmware();

  Serial.println("Access Point Web Server");

  if (WiFi.status() == WL_NO_SHIELD)
  {
    Serial.println("WiFi shield not present");
    errorProtocol();
  }

  WiFi.config(ip);

  Serial.print("Creating access point named: ");
  Serial.println(ssidName);

  status = WiFi.beginAP(ssidName, 1, password);
  if (status != WL_AP_LISTENING)
  {
    Serial.println("Creating access point failed");
    errorProtocol();
  }
  delay(10000);
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
  server.begin();
}

//========================================================================

void reportConnection()
{
  if (status != WiFi.status())
  {
    status = WiFi.status();

    if (status == WL_AP_CONNECTED)
    {
      byte remoteMac[6];
      Serial.print("Device connected to AP, MAC address: ");
      WiFi.APClientMacAddress(remoteMac);
      Serial.print(remoteMac[5], HEX);
      Serial.print(":");
      Serial.print(remoteMac[4], HEX);
      Serial.print(":");
      Serial.print(remoteMac[3], HEX);
      Serial.print(":");
      Serial.print(remoteMac[2], HEX);
      Serial.print(":");
      Serial.print(remoteMac[1], HEX);
      Serial.print(":");
      Serial.println(remoteMac[0], HEX);
    }
    else
    {
      Serial.println("Device disconnected from AP");
    }
  }
}

//========================================================================

void getDataFromClient()
{
  WiFiClient client = server.available();   // listen for incoming clients

  if (client)
  {

    pinMode(LED_BUILTIN, OUTPUT);

    while (client.connected())
    { 
      String currentLine = ""; 
      if (client.available())
      {
        char c = client.read();
        while (c != '\r' || c != '\n')
        {
          currentLine += c;      // add it to the end of the currentLine
          c = client.read();             // read a byte, then
          
        }
      }
      if (currentLine.length() != 0)
      {
        Serial.println(currentLine);
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
//========================================================================
