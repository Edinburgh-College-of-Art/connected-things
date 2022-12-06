JSONVar getWeather()
{
  // static const char* host = "ip.jsontest.com";
  static const char* host = "api.open-meteo.com";
  static const char* url  = "/v1/forecast?latitude=52.52&longitude=13.41&hourly=temperature_2m,relativehumidity_2m,windspeed_10m";
  // static const char* url = "/";
  Serial.print(host);
  Serial.println(url);
  httpRequest(host, url);
  return JSON.parse(waitForHttpResponse().c_str());
}

float getTodaysTemperatureAtHour(int hour)
{

  JSONVar weather = getWeather();
  return float((double)(weather["hourly"]["temperature_2m"][hour % 24]));
}