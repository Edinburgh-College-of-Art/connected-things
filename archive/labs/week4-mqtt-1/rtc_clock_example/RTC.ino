// setRTC ---------------------------------
void setRTC()
{
  rtc.begin(); // start the real-time clock

  String currentTime = getCurrentTime(); // call the getCurrentTime() function (see below) to make a GET request to the World Time API and return the current time as a String
  Serial.println("Current Time: " + currentTime); // Print the retrieved time to the Serial port

  // The RTCZero library expects a number to set the time so we have to convert the returned String to ints
  // First use the Arduino's substring() function to create a new String and extract the current hour
  // Basically what this is doing is cutting out the parts of the String we don't want, and keeping the bits we do
  // More info on what substring() does and how it works can be found here: https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/substring/
  String cHour = currentTime.substring(0, 2);
  Serial.println(cHour); // print the current hour to the Serial port

  String cMin = currentTime.substring(3, 5); // Create another new string and extract the current minute
  Serial.println(cMin); // print the current minute to the Serial port

  int setH = cHour.toInt(); // convert the values for the current hour and current to ints (whole numbers)
  int setM = cMin.toInt();

  rtc.setTime(setH, setM, 0); // use these values to set the clock on the Arduino
  rtc.setDate(05, 02, 20); // Put values here to set the current date DD, MM, YY – you could also get this from the World Time API if you wanted

}
// getCurrentTime -----------------------
String getCurrentTime()  // This is a non-void function – which returns a String
{
  String timeJSON = getJson("worldtimeapi.org", "/api/timezone/Europe/London.json", 80); // call the getJson function (on the worldtime_api tab)
  // The values you are passing in here are the host name of the server you want to connect to, your request URL, and the port number you want to use (80 means unsecured connection)
  // The data will be returned as a String, which we then need to convert to a JSON Object to parse

  // First create a new DynamicJsonDocument – the number that goes in here allocates memory on the Arduino for the data you download from the server
  // Make sure you allocate enough memory for the JSON you want to download or your Arduino will crash and you will need to manually reset it
  // To calculate the memory required, use your web browser to call the API and view the response in your browser by pasting your full GET request into the address bar,
  // and copy and paste the response you get into the ArduinoJson assistant on this page: https://arduinojson.org/v6/assistant/
  // You can also use the ArduinoJson assistant to help you write code to parse your JSON – see pages 12 – 14 of the 'Parsing Json' slides on Learn for an example

  DynamicJsonDocument jsonBuffer(400);

  deserializeJson(jsonBuffer, timeJSON); // Next, use this code to copy the data in the String returned by the getJson function into a JSON Object
  JsonObject timeRoot = jsonBuffer.as<JsonObject>();

  String timeString = timeRoot["utc_datetime"]; // extract the value for "utc_datetime" from the returned JSON
  Serial.println(timeString); // print the data to the Serial
  String cTime = timeString.substring(11, 16); // use the Arduino function substring() to create another string and extract the current time
  Serial.println(cTime);  // print the new String to the Serial

  return cTime; // return the String called cTime – which holds only the current time

}
