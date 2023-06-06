void checkWeather()
{
  long unixTime = getCurrentTime(); // This line gets the current Unix Time by calling the World Time API (see getCurrentTime tab)

  String darkSkyApiKey = "your_api_key"; // Replace this with your own Dark Sky API Key
  String host = "api.darksky.net"; // Create a String to hold the address of the server you want to connect to
  String url = "/forecast/" + darkSkyApiKey + "/55.864473,-4.251814," + String(unixTime) + "?exclude=minutely,hourly,alerts,flags"; // Create a String to hold the URL for your GET Request
  const int port = 443; // Create an int to specify the Port Number you want to use – here we are using 443 for a secure connection

  String weatherForecast = getJson(host, url, port); // Create a new String to hold the JSON response from the API, and call the getJson function (on JSON_Utils tab) to download it
  // The data will be returned as a String, which we then need to convert to a JSON Ojbect to parse

  /*First, create a new DynamicJson Document – the number that goes in the brackets here allocates memory on the Arduino for the data you download from the server
     Make sure you allocate enough memory for the JSON you want to download or your Arduino will crash and you will need to manually reset it
     To calculate the memory required, use your web browser to call the API by pasting your full GET request into the address bar,
     and then copy and past the response you get into the ArduinoJson Assistant on this page: https://arduinojson.org/v6/assistant/
     You can also use the ArduinoJson assistant to help you write code to parse your JSON – see pages 12 – 14 of the 'Parsing JSON' slides on Learn for an example */

  DynamicJsonDocument jsonBuffer(2048);
  deserializeJson(jsonBuffer, weatherForecast); // Next, copy the data in the String returned by the getJson function into a JSON Object
  JsonObject json = jsonBuffer.as<JsonObject>();

  String weather = json["currently"]["icon"];
  Serial.println("Current weather: " + weather);

  // Like the Paper Signals example from Week 2 – here we are using the "icon" value in the returned JSON
  // The RGB LED will turn a different colour depending on the weather indicated by "icon"

  if (weather == "rain" || weather == "snow" || weather == "sleet")
  {
    setLEDcolour(255, 0, 0); // red
  }
  else if (weather == "fog" || weather == "cloudy" || weather == "wind")
  {
    setLEDcolour(0, 0, 255); // blue
  }
  else if (weather == "clear-day" || weather == "clear-night")
  {
    setLEDcolour(0, 255, 0); // green
  }
  else
  {
    setLEDcolour(255, 0, 255); // pink
  }
  // clear-day, clear-night, rain, snow, sleet, wind, fog, cloudy, partly-cloudy-day, partly-cloudy-night

}
