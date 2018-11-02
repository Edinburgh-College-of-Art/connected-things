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
  WiFiClient client = server.available();   // listen for incoming clients
  
  if (client)
  { // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    pinMode(LED_BUILTIN, OUTPUT);
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected())
    { // loop while the client's connected
      if (client.available())
      { // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n')
        { // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0)
          {
            //------------------------------------------------------------------------
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            //------------------------------------------------------------------------
            // the content of the HTTP response follows the header:
            client.print("Click <a href=\"/H\">here</a> turn the LED on<br>");
            client.print("Click <a href=\"/L\">here</a> turn the LED off<br>");
            //------------------------------------------------------------------------
            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else
          { // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r')
        { // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
        
        if (currentLine.endsWith("GET /H")) // Check to see if the client request was "GET /H" or "GET /L":
        {
          digitalWrite(LED_BUILTIN, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L"))
        {
          digitalWrite(LED_BUILTIN, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}
//========================================================================
