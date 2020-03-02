// This example uses the Dark Sky API, but the general format of this code will work for any API you are requesting JSON data from

void checkWeather() {

  String darkSkyApiKey = "your_api_key"; // replace this with your own API key for Dark Sky
  String host = "api.darksky.net"; // put the host name of the API you want to connect to here
  String url = "/forecast/" + darkSkyApiKey + "/55.864473,-4.251814,1580817600?exclude=minutely,hourly,currently,alerts,flags"; // build the URL for your GET request
  // The values here are the latitude and longitude for Glasgow (55.864473,-4.251814), the UNIX time for the forecast we want in this case 12noon on 4th February 2020
  // and the parameters we want to exclude from the JSON data we get back (so we don't get an enormous block of JSON with a week's worth of forecasts)

  String weatherForecast = getJson(host, url); // this line calls the function getJson (on the HTTP_Requests tab of this sketch) to send the GET request and download the data
  // The data will be returned as a String, which we then need to convert to a JSON Object to parse

  // First create a new DynamicJsonDocument – the number that goes in here allocates memory on the Arduino for the data you download from the server
  // Make sure you allocate enough memory for the JSON you want to download or your Arduino will crash and you will need to manually reset it
  // To calculate the memory required, use your web browser to call the API and view the response in your browser by pasting your full GET request into the address bar,
  // and copy and paste the response you get into the ArduinoJson assistant on this page: https://arduinojson.org/v6/assistant/
  // You can also use the ArduinoJson assistant to help you write code to parse your JSON – see pages 12 – 14 of the 'Parsing Json' slides for an example
  DynamicJsonDocument jsonBuffer(2048);

  deserializeJson(jsonBuffer, weatherForecast); // Next, use this code to copy the data in the string returned by the getJson function into a JSON Object
  JsonObject json = jsonBuffer.as<JsonObject>();

  // A copy of the JSON Document this code is parsing is on page 9 of the 'Parsing JSON' Slides on Learn
  // Remember to extract a value from a JSON Document, you need to tell Arduino where to go

  String latitude = json["latitude"];
  String longitude = json["longitude"];
  Serial.println("Latitude: " + latitude + ", Longitude:" + longitude); // Print the values you extracted to the Serial port

// In these examples, the data in the JSON is a String – this is indicated by the double quotation marks around the entry on the right of the colon
// e.g. "summary" : "Windy in the morning.", 
  String summary = json["daily"]["data"][0]["summary"]; // Here for example, you are telling it to go to the "daily" object, then the "data" array, go to the first entry in the array ( [0] ), then go to the value "summary"
  Serial.println("Summary: " + summary);

  String windSpeed = json["daily"]["data"][0]["windSpeed"];
  Serial.println("Wind Speed: " + windSpeed);

  String windGust = json["daily"]["data"][0]["windGust"];
  Serial.println("Wind Gust: " + windGust);

// In these examples, the data in the JSON is a float – we can tell this because there are no quotation marks around the entry on the right of the colon
// and the number has a decimal point, e.g. "temperatureHigh" : 47.88, 
  float temperatureHigh = json["daily"]["data"][0]["temperatureHigh"]; 
  float temperatureLow = json["daily"]["data"][0]["temperatureLow"];
  Serial.println("High: " + String(temperatureHigh) + ", Low: " + String(temperatureLow));

}
