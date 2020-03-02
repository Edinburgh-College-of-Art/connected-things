// The code on this tab demonstrates how to get the current Unix Time from the World Time API
// The general format of the code will, however, work for any API you are requesting JSON data from
// Note that accessing the World Time API does not require an API Key

long getCurrentTime() {

  String host = "worldtimeapi.org"; // Create a String to hold the address of the server you want to connect to
  String url = "/api/timezone/Europe/London.json"; // Create a string to hold the URL for your GET Request
  const int port = 80; // Create an int to hold your Port Number – in this case we are using Port 80 for an unsecured connection

  String timeJson = getJson(host, url, port); // Create a new String to hold the JSON response from the API, and call the getJson function (on JSON_Utils tab) to download it
  // The data will be returned as a String, which we then need to convert to a JSON Ojbect to parse

  /*First, create a new DynamicJson Document – the number that goes in the brackets here allocates memory on the Arduino for the data you download from the server
    Make sure you allocate enough memory for the JSON you want to download or your Arduino will crash and you will need to manually reset it
    To calculate the memory required, use your web browser to call the API by pasting your full GET request into the address bar,
    and then copy and past the response you get into the ArduinoJson Assistant on this page: https://arduinojson.org/v6/assistant/
    You can also use the ArduinoJson assistant to help you write code to parse your JSON – see pages 12 – 14 of the 'Parsing JSON' slides on Learn for an example */

  DynamicJsonDocument jsonBuffer(500);
  deserializeJson(jsonBuffer, timeJson); // Next, copy the data in the String returned by the getJson function into a JSON Object
  JsonObject timeData = jsonBuffer.as<JsonObject>();

  long unixTime = timeData["unixtime"]; // Create a new long to hold the returned Unix Time, and extract the value from the JSON Object
  Serial.println("Current Unix Time: " + String(unixTime)); // Print the returned value to the Serial

  return unixTime; // return the long called unixTime

}
