unsigned int makeGetRequest(String &host, String &url)
{
  Serial.println("https://" + host + url);
  unsigned int contentLength;
  bool chunked = false;
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
      chunked = true;
    }
    else if (line.startsWith("Transfer-Encoding: chunked"))
    {
      Serial.println("WARNING CHUNKED ENCODING: Email the lecturer");
      haltFirmware();
    }
    else if (line == "\r")
    {
      break;
    }
  }
  return contentLength;
}

//---------------------------------------------------------------------------------------------------------------------------------------

unsigned int makeSSLGetRequest(String &host, String &url)
{
  Serial.println("https://" + host + url);
  unsigned int contentLength;
  bool chunked = false;
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
      //      haltFirmware();
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
  bool chunked = true;
  if (contentLength > 10000)
  {
    chunked = true;
    Serial.print("Your Content Length is: ");
    Serial.println(contentLength);
    Serial.println("Maybe use another request or API");
    //    haltFirmware();
  }

  unsigned int byteCounter = 0;
  unsigned int charCounter = 0;

  if (chunked)
  {
    parseChunked();
  }
  else
  {
    parseContent(contentLength);
  }



  Serial.print("\n DONE\n");
  DynamicJsonDocument buffer(charCounter);
  deserializeJson(buffer, httpResponse);
  return buffer.as < JsonObject > ();
}

//---------------------------------------------------------------------------------------------------------------------------------------

JsonObject makeAPIcall(String & host, String & url)
{
  unsigned int contentLength = makeGetRequest(host, url);

  if (contentLength > 10000)
  {
    Serial.print("Your Content Length is: ");
    Serial.println(contentLength);
    Serial.println("Maybe use another request or API");
    haltFirmware();
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

//---------------------------------------------------------------------------------------------------------------------------------------

void parseChunked()
{
  char p = 0;
  unsigned int charCounter = 0;

  String first = "";

  while (first == "")
  {
    first = sslClient.readStringUntil('\n');
  }
  
  while (true)
  {
    // parse first number!!!!
    char t = sslClient.read();
    if (t != 255)
    {
      Serial.print(t);
      if (p == '0')
      {
        if (t == 13)
        {
          Serial.print("end");
          charCounter--;
          break;
        }

      }
      else
      {
        if (t != ' ' && t != '\r' && t != '\n') // PARSE OUT last "0" from result
        {
          httpResponse[charCounter] = t;
          charCounter++;
          if (charCounter == 10000)
          {
            Serial.println("response is too large to parse");
            haltFirmware();
          }
        }
      }
      p = t;
    }

  }
//  haltFirmware();
}

//---------------------------------------------------------------------------------------------------------------------------------------

void parseContent(unsigned int contentLength)
{
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
}
