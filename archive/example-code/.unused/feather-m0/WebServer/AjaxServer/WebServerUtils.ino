//========================================================================

void setAccessPoint(const char ssidName[], IPAddress ip)
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

  status = WiFi.beginAP(ssidName);
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

void deliverWebsite()
{
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("new client");
    if (client.available())
    {
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();

      if (request.startsWith("GET /"))
      {
        //------------------------------------------------------------------------
        client.println("HTTP/1.1 200 OK");
        client.println("Content-type:text/html");
        client.println();
        String pageRequest = request.substring(4);
        //------------------------------------------------------------------------
        // the content of the HTTP response follows the header:
        if (pageRequest.startsWith("/ "))
        {
          client.print("<h1>Main Page</h1>");
          client.println();
        }
        if (pageRequest.startsWith("/data"))
        {
//          <!DOCTYPE html>
//<html lang="en">
//<head>
//    <meta charset="UTF-8">

          client.print(analogRead(A0));
          client.println();         
        }
        if (pageRequest.startsWith("/test"))
        {          
          client.println(htmlPage);
          client.println();
        }
      }
    }
  }
  client.flush();
  client.stop();
}

//========================================================================
