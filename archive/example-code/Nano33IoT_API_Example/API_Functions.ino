JSONVar getWeather() {
  // static const char* host = "ip.jsontest.com";
  static const char* host = "api.open-meteo.com";
  static const char* url = "/v1/forecast?latitude=52.52&longitude=13.41&hourly=temperature_2m";
  // static const char* url = "/";
  Serial.print(host);
  Serial.println(url);
  httpRequest(host, url);
  String response = waitForHttpResponse();
  Serial.println(response);
  DynamicJsonDocument doc(4000);
  deserializeJson(doc, response);
  JsonObject obj = doc.as<JsonObject>();
  Serial.println("Before Function");
  float lat = obj["latitude"];
  Serial.println(lat);
  return JSON.parse(response);
}

float getTodaysTemperatureAtHour(int hour) {
  JsonObject weather = getWeather();
  Serial.println("Test");
  Serial.println(JSON.typeof_(weather));
  return float((double)(weather["hourly"]["temperature_2m"][0]));
}