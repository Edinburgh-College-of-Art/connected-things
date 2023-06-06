String getJson(String host, String url, const int port, bool debug)
{
  if (debug)
  {
    Serial.print("connecting to ");
    Serial.println(host);
  }
  String payload;
  if (port == 80)
  {
    if (client.connect(host.c_str(), 80))
    {
      if (debug)
        Serial.println("connected to server");

      client.println("GET " + url + " HTTP/1.1");
      client.println("Host: " + host);
      client.println("Connection: close");
      client.println();

      if (debug)
        Serial.println("request sent");
    }
    else
    {
      Serial.println("connection failed");
      return "bad";
    }

    while (client.connected())
    {
      String line = client.readStringUntil('\n');
      if (debug)
      {
        Serial.println(line);
      }
      if (line == "\r")
      {
        if (debug)
        {
          Serial.println("headers received");
        }
        break;
      }
    }
    payload = client.readString();
  }
  else
  {
    if (sslClient.connect(host.c_str(), port))
    {
      if (debug)
        Serial.println("connected to server");

      sslClient.println("GET " + url + " HTTP/1.1");
      sslClient.println("Host: " + host);
      sslClient.println("Connection: close");
      sslClient.println();

      if (debug)
        Serial.println("request sent");
    }
    else
    {
      Serial.println("connection failed");
      return "bad";
    }

    while (sslClient.connected())
    {
      String line = sslClient.readStringUntil('\n');
      if (debug)
        Serial.println(line);

      if (line == "\r")
      {
        if (debug)
          Serial.println("headers received");

        break;
      }
    }
    payload = sslClient.readString();
  }

  if (debug)
  {
    Serial.println("reply was:");
    Serial.println("==========");
    Serial.println(payload);
    Serial.println("==========");
  }
  return payload;
}
