// setRTC ---------------------------------
void setRTC() {

  rtc.begin(); // Start the real-time clock

  int epoch = getCurrentTime(); // Call the getCurrentTime() function (see below) to make a GET request to the World Time API and return the current Unix Time as an int

  rtc.setEpoch(epoch); // Set the real-time clock using the returned Unix Time

  int h = rtc.getHours(); // Use this to check the clock is set correctly
  int m = rtc.getMinutes();
  Serial.println("Time from Clock: " + String(h) + ":" + String(m)); // Print the current time to the Serial port

}


// getCurrentTime -----------------------
int getCurrentTime() { // This is a non-void function – which returns an int

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

  int unixTime = timeRoot["unixtime"]; // Extract the current Unix Time from the returned JSON
  Serial.print("Current Unix Time: "); // Print the value you get to the Serial
  Serial.println(unixTime);

  return unixTime; // Return the unixTime int

}


// setAlarm ---------------------------
// IMPORTANT NOTE: You can only set one alarm at a time.
// If you want to set more than one alarm, you will have to write some code to set a new alarm after each one is triggered.
void setAlarm() {

  rtc.setAlarmTime(12, 0, 0); // Set the time you want the alarm to be triggered by passing in the hour, minutes, and seconds
  rtc.enableAlarm(rtc.MATCH_HHMMSS); // Enable the alarm for when the time matches the time you just set above
  rtc.attachInterrupt(alarm); // Use attachInterrupt() to specifiy the function you want to call – in this case it is the alarm() function (on main tab)
  Serial.println("Alarm is set!"); // Print a message to the Serial to confirm the alarm is set

}
