String getLatLong(String location)
{
  //----------------------------------------------------------------------------
  location = urlencode(location);
  String geoHost = "geocode.xyz";
  String geoURL  = "/" + location + "?json=1";
  //----------------------------------------------------------------------------
  String LatLongPayload = getJson(geoHost, geoURL, 80, false); // Get Lat Long
  //  Serial.println(LatLongPayload);
  //----------------------------------------------------------------------------
  DynamicJsonDocument jsonBuffer(512);
  deserializeJson(jsonBuffer, LatLongPayload);
  JsonObject jsonObj = jsonBuffer.as<JsonObject>();
  //----------------------------------------------------------------------------
  String latString = jsonObj["alt"]["loc"]["latt"];
  String lngString = jsonObj["alt"]["loc"]["longt"];
  return latString + "," + lngString;
}
//------------------------------------------------------------------------------
String getWeather(String location)
{
  String latLong = getLatLong(location);

  return getLatLngWeather(latLong);
}
//------------------------------------------------------------------------------
String getWeather (String lat, String lng)
{
  String latLong = lat + "," + lng;

  return getLatLngWeather(latLong);
}

String getLatLngWeather(String latLong)
{
  String unixTime = getCurrentUnixTime();
  //  Serial.println("unix time: " + unixTime);
  unsigned long unixTimeLong = atol(unixTime.c_str()) + 10000;
  String finalUnixTime = String(unixTimeLong);
  //  Serial.println(finalUnixTime);

  String weatherHost = "api.darksky.net";
  String weatherURL = "/forecast/" +
                      DarkSkyAPIKey + "/" +
                      latLong + "," +
                      finalUnixTime +
                      "?exclude=minutely,flags,hourly,currently,alerts";
  //  Serial.println("Weather URL: " + weatherHost + weatherURL);
  String weatherPayload = getJson(weatherHost, weatherURL, 443, false); // Get Weather
  //  Serial.println(weatherPayload);
  return weatherPayload;
}


String getCurrentUnixTime()
{
  String timeJSON = getJson("worldtimeapi.org", "/api/timezone/Europe/London.json",  80, false);
  DynamicJsonDocument jsonBuffer(400);
  deserializeJson(jsonBuffer, timeJSON);
  JsonObject timeRoot = jsonBuffer.as<JsonObject>();
  return timeRoot["unixtime"];
}
//------------------------------------------------------------------------------
bool itIsGoingToRain(String location)
{
  String WeatherJSON = getWeather(location);
  
  DynamicJsonDocument jsonBufferWeather(2048);
  deserializeJson(jsonBufferWeather, WeatherJSON);
  JsonObject weatherRoot = jsonBufferWeather.as<JsonObject>();
  
  String iconWeather = weatherRoot["daily"]["data"][0]["icon"];
  Serial.println(iconWeather);

  String rainIcon = "rain";
  String sleetIcon = "sleet";
  String snowIcon = "snow";

  return (iconWeather == rainIcon  ||
          iconWeather == sleetIcon ||
          iconWeather == snowIcon) ? true : false;
}
//------------------------------------------------------------------------------
String urlencode(String str)
{
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ')
    {
      encodedString += "%20";
    }
    else if (isalnum(c))
    {
      encodedString += c;
    }
    else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9)
      {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9)
      {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      //encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}
