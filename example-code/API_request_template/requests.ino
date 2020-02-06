unsigned int makeGetRequest(String &host, String &url)
{
  Serial.println("https://" + host + url); // I have included this line to help you test your HTTP request
  unsigned int contentLength;

  if (client.connect(host.c_str(), 443))
  {
    Serial.println("Connecting to carbon intensity."); // Print a message to the Serial port to let you know the connection has been successful
    client.println("GET " + url + " HTTP/1.1"); // Send your GET request to Dark Sky
    client.println("Host: " + host);
    client.println("TE: chunked");
    client.println("Connection: close"); // Close the connection
    client.println(); // Remember to include a line break at the end of your request
  }
  Serial.println(client.available());
  while (client.connected())
  {
    String line = client.readStringUntil('\n'); // Read in the data it sends you
    Serial.println(line);
    if (line.startsWith("Content-Length: "))
    {
      contentLength = getContentLength(line);
    }

    if (line == "\r")
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
JsonObject makeAPIcall(String &host, String &url)
{
  unsigned int contentLength = makeGetRequest(host, url);
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

  // Before we can parse the data we need to convert it from a String to a JSON Object
  DynamicJsonDocument buffer(charCounter); // First create a new DynamicJsonDocument and allocate space in the Arduino's memory to hold it
  deserializeJson(buffer, httpResponse); // Then you need to to deserialize the JSON – this basically means converting it into a representation that Arduino can work with
  return buffer.as < JsonObject > ();
}
