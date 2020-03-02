// The code on this tab is a general template for making an API call, which you can adapt depending on the API you want to talk to
// I would recommend having a seperate function, on a seperate tab for each API call you want to make in a program
// For instance, if you have a program that is talking to both Dark Sky and IFTTT – use this code as the basis to write two functions,
// for instance, one called callIFTTT() and another called callDarkSky()

void apiCall() {

  String host = "your_host"; // Replace with the host name API you want to call
  String apiKey = "your_api_key"; // Remember, not all APIs will require a key
  String url = "your_request_url"; // What you put here will depend on the individual API – look at example requests in its API Documentation for the format
  const int port = 443; // Replace with the port number you want to use (Unsecured = 80; Secured = 443)

  // Call the getJson function, and pass in the values for host, url, and port
  String jsonResponse = getJson(host, url, port);

  // Remember – the number in the brackets here allocates space in the Arduino memory to hold the JSON returned by the server
  // Use the ArduinoJson Assistant to find how big this number needs to be: https://arduinojson.org/v6/assistant/
  DynamicJsonDocument jsonBuffer(2048);
  deserializeJson(jsonBuffer, jsonResponse);
  JsonObject json = jsonBuffer.as<JsonObject>();

  // Do something with the data you get back...

}
