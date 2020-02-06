unsigned int makeGetRequest(String &host, String &url)
{
  Serial.println("https://" + host + url);
  unsigned int contentLength;

  if (client.connect(host.c_str(), 80))
  {
    Serial.println("Connecting to carbon intensity.");
    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: " + host);
    client.println("Connection: close");
    client.println();
  }
  Serial.println(client.available());
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    Serial.println(line);
    if (line.startsWith("Content-Length: "))
    {
      contentLength = getContentLength(line);
    }
    else if (line.startsWith("Transfer-Encoding: chunked"))
    {
      Serial.println("WARNING CHUNKED ENCODING: Email the lecturer");
      haltFirmare();
    }
    else if (line == "\r")
    {
      break;
    }
  }
  return contentLength;
}


unsigned int makeSSLGetRequest(String &host, String &url)
{
  Serial.println("https://" + host + url);
  unsigned int contentLength;

  if (sslClient.connectSSL(host.c_str(), 443))
  {
    Serial.println("Connecting to carbon intensity.");
    sslClient.println("GET " + url + " HTTP/1.1");
    sslClient.println("Host: " + host);
    sslClient.println("Connection: close");
    sslClient.println();
  }
  Serial.println(sslClient.available());
  while (sslClient.connected())
  {
    String line = sslClient.readStringUntil('\n');
    Serial.println(line);
    if (line.startsWith("Content-Length: "))
    {
      contentLength = getContentLength(line);
    }
    else if (line.startsWith("Transfer-Encoding: chunked"))
    {
      Serial.println("WARNING CHUNKED ENCODING: Email the lecturer");
      haltFirmare();
    }
    else if (line == "\r")
    {
      break;
    }
  }
  return contentLength;
}

//---------------------------------------------------------------------------------------------------------------------------------------

unsigned int getContentLength(String line)
{
  return line.substring(16).toInt(); // This line prints out the response from Carbon Intensity to the Serial Monitor – this will let you know if your request was successful
}

//---------------------------------------------------------------------------------------------------------------------------------------
JsonObject makeSSLAPIcall(String &host, String &url)
{
  unsigned int contentLength = makeSSLGetRequest(host, url);

  if (contentLength > 10000)
  {
    Serial.print("Your Content Length is: ");
    Serial.println(contentLength);
    Serial.println("Maybe use another request or API");
    haltFirmare();
  }

  unsigned int byteCounter = 0;
  unsigned int charCounter = 0;
  while (true)
  {
    char t = sslClient.read();

    if (t != 255)
    {
      if (t != ' ' && t != '\r' && t != '\n')
      {
        httpResponse[charCounter] = t;
        charCounter++;
      }
      byteCounter++;
      if (byteCounter == contentLength)
      {
        Serial.println(byteCounter);
        break;
      }
    }
  }

  for (int i = 0; i < charCounter; i++)
  {
    Serial.print(httpResponse[i]);
  }

  Serial.print("\n DONE\n");
  DynamicJsonDocument buffer(charCounter);
  deserializeJson(buffer, httpResponse);
  return buffer.as < JsonObject > ();
}

JsonObject makeAPIcall(String &host, String &url)
{
  unsigned int contentLength = makeGetRequest(host, url);

  if (contentLength > 10000)
  {
    Serial.print("Your Content Length is: ");
    Serial.println(contentLength);
    Serial.println("Maybe use another request or API");
    haltFirmare();
  }

  unsigned int byteCounter = 0;
  unsigned int charCounter = 0;
  while (true)
  {
    char t = client.read();

    if (t != 255)
    {
      if (t != ' ' && t != '\r' && t != '\n')
      {
        httpResponse[charCounter] = t;
        charCounter++;
      }
      byteCounter++;
      if (byteCounter == contentLength)
      {
        Serial.println(byteCounter);
        break;
      }
    }
  }

  for (int i = 0; i < charCounter; i++)
  {
    Serial.print(httpResponse[i]);
  }
  

  DynamicJsonDocument buffer(charCounter);
  deserializeJson(buffer, httpResponse);
  return buffer.as < JsonObject > ();
}
