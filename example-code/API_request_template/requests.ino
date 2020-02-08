unsigned int makeGetRequest(String &host, String &url, Client &httpClient, int port, bool &chunked)
{

  Serial.println(((port == 443) ? ("https://") : ("http://")) + host + url);
  unsigned int contentLength;
  chunked = false;

  if (httpClient.connect(host.c_str(), port))
  {
    Serial.println("Connecting to carbon intensity.");
    httpClient.println("GET " + url + " HTTP/1.1");
    httpClient.println("Host: " + host);
    httpClient.println("Connection: close");
    httpClient.println();
  }
  else
  {
    Serial.println("Connection Failed; check:\n\t- did WiFi Connect?\n\t- is the site HTTPS?\n\t- have you used the correct client? v(WiFiClient or WiFiSSLClient)\n\t- have you selected the correct port? (80 or 443)\n");
    haltFirmware();
  }

  while (httpClient.connected())
  {
    String line = httpClient.readStringUntil('\n');
    Serial.println(line);
    if (line.startsWith("Content-Length: "))
    {
      contentLength = getContentLength(line);
    }
    else if (line.startsWith("Transfer-Encoding: chunked"))
    {
      Serial.println("WARNING CHUNKED ENCODING: Email the lecturer");
      chunked = true;
    }
    else if (line == "\r")
    {
      break;
    }
  }
  return contentLength;
}

JsonObject makeAPIcall(String & host, String & url, Client &httpClient, int port)
{
  bool chunked = false;
  int contentLength = makeGetRequest(host, url, httpClient, port, chunked);
  unsigned int charCount;
  if (chunked)
  {
    charCount = parseChunked(httpClient);
  }
  else if (contentLength > CHARACTER_LIMIT)
  {
    Serial.print("Your Content Length is: ");
    Serial.println(contentLength);
    Serial.println("Maybe use another request or API");
    haltFirmware();
  }
  else
  {
    charCount = parseContent(contentLength, httpClient);
  }

  printHttpResponse(charCount);

  DynamicJsonDocument buffer(charCount);
  deserializeJson(buffer, httpResponse);
  return buffer.as < JsonObject > ();
}

//---------------------------------------------------------------------------------------------------------------------------------------

unsigned int getContentLength(String line)
{
  return line.substring(16).toInt(); // This line prints out the response from Carbon Intensity to the Serial Monitor – this will let you know if your request was successful
}


//---------------------------------------------------------------------------------------------------------------------------------------

unsigned int parseChunked(Client &httpClient)
{
  char p = 0;
  unsigned int charCounter = 0;

  String firstNumber = "";

  while (firstNumber == "")
  {
    firstNumber = httpClient.readStringUntil('\n');
  }

  while (true)
  {
    char t = httpClient.read();
    if (t != 255)
    {
      if (p == '0')
      {
        if (t == 13)
        {
          charCounter--; // PARSE OUT last "0" from result
          break;
        }
      }
      else
      {
        if (t != ' ' && t != '\r' && t != '\n') 
        {
          httpResponse[charCounter] = t;
          charCounter++;
          if (charCounter == CHARACTER_LIMIT)
          {
            Serial.println("response is too large to parse");
            haltFirmware();
          }
        }
      }
      p = t;
    }

  }
  return charCounter;
}

//---------------------------------------------------------------------------------------------------------------------------------------

unsigned int parseContent(unsigned int contentLength, Client &httpClient)
{
  unsigned int byteCounter = 0;
  unsigned int charCounter = 0;
  while (true)
  {
    char t = httpClient.read();

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
  return charCounter;
}

//---------------------------------------------------------------------------------------------------------------------------------------


void printHttpResponse(unsigned int charCount)
{
  for (int i = 0; i < charCount; i++)
  {
    Serial.print(httpResponse[i]);
  }
  Serial.println();
}
