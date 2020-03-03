// This sketch demonstrates how to connect to the Dark Sky API, download a weather forecast and move a Servo.
// Remember if you are using one of the Feathers you will need to makes sure the Dark Sky API has been added to the SSL Certificates
// Instructions here: https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/updating-ssl-certificates
// Instructions to build the Umbrella Paper Signal are here: https://papersignals.withgoogle.com/getstarted
// If you need a reminder of how to wire a Servo: https://www.arduino.cc/en/tutorial/sweep

// The first thing you need to do is add the required libraries
//#include <WiFiNINA.h> // Use this WiFi library if running this sketch on an Arduino Nano 33 IoT board (the one in your kit)
#include <WiFi101.h> // Use this WiFi library if running this sketch on Feather M0 board
#include <Servo.h> // This library allows you to control a Servo attached to the Arduino
#include <ArduinoJson.h> // This library is for handling JSON Data in Arduino

// WiFi Connection -----------------------
const char* ssid = "HANABI"; // If you are not at ECA, replace these with the name and password for your local wi-fi network
const char* password = "lowernorwood";

// Dark Sky API --------------------------
String apiKey = "your_api_key"; // Replace this with your own API Key from the Dark Sky website
String host = "api.darksky.net"; // Create a string to hold the name of the host you are connecting to
String url = "/forecast/" + apiKey + "/55.94100,-3.20356,1578665400?exclude=minutely,flags,hourly,currently,alerts"; // create a string to hold your HTTP request URL
// Remember the numbers we're using here are the latitude and longitude for Edinburgh (55.94100, -3.20356), the UNIX time for the forecast we want (1578665400)
// The UNIX time in this example is still set to January 10th, so you will need to change it for an up-to-date forecast
// The final part of the URL (?exclude...) is telling Dark Sky to exclude the named data blocks from the API response
// For more info on how to build a request URL for Dark Sky, refer to the API Docs: https://darksky.net/dev/docs

// WiFi Client --------------------------
WiFiSSLClient client; // Create a new WiFi SSL Client – this will give us a secure connection (https) to Dark Sky through port 443

// Servo --------------------------------
Servo myServo; // Create a new Servo object and give it a name
int currentServoPos = 0; // Create a new int to keep track of the Servo's current position
#define CENTER_POS 90 // Define three variables to store the different positions the servo needs to move to (to open or close your Paper Signal umbrella)
#define UMBRELLA_OPEN 60
#define UMBRELLA_CLOSED 180

// Timer --------------------------------
long timer = 300000; // We will use this long in the main loop to control how often Arduino sends HTTP Requests to the Dark Sky API
// The value you put here is the time in milliseconds you want to wait between API calls – in this case 300000 ms = 5 minutes


// Setup -------------------------------
void setup()  // runs once
{
  connectToWifi(ssid, password); // Call the function that connects the Arduino to WiFi – passing in the values for ssid and password created above

  Serial.println("https://" + host + url); // I have included this line to help you test your HTTP request
  // This will print your full HTTP request URL to the Serial port – if you copy and paste it into your web browser you can check if your request is working correctly

  myServo.attach(9); // This line tells the Arduino which pin the Servo is attached to - change the number in the brackets to match the pin yours is connected to
  moveServoToPos(CENTER_POS, 10); // Call the moveServo() function to move the servo to its starting position at a speed of 10
}
// Loop ---------------------------------
void loop()  // runs continuously
{
  checkWeather(); // call the checkWeather function to get a forecast from Dark Sky
  delay(timer); // do nothing for the next five minutes – make sure you include this or you will very quickly hit your rate limit on Dark Sky!

}
// Check the Weather ----------------------
void checkWeather()
{
  if (client.connect(host.c_str(), 443))  // Connect to the client (Dark Sky API) using port 443 (secure connection)
  {
    Serial.println("Connected to Dark Sky."); // Print a message to the Serial port to let you know the connection has been successful
    client.println("GET " + url + " HTTP/1.1"); // Send your GET request to Dark Sky
    client.println("Host: " + host);
    client.println("Connection: close"); // Close the connection
    client.println(); // Remember to include a line break at the end of your request
  }

  while (client.connected())  // While you are connected to Dark Sky
  {
    String line = client.readStringUntil('\n'); // Read in the data it sends you
    if (line == "\r")  // until you hit a line break
    {
      break;
    }
    Serial.println(line); // This line prints out the response from Dark Sky to the Serial Monitor – this will let you know if your request was successful
  }

  String jsonString = client.readString(); // Read in the JSON data returned from Dark Sky as a String
  Serial.println(jsonString); // Print the result to the Serial port – this will display the JSON data you've received from Dark Sky

  // Before we can parse the data we need to convert it from a String to a JSON Object
  DynamicJsonDocument buffer(2048); // First create a new DynamicJsonDocument and allocate space in the Arduino's memory to hold it
  deserializeJson(buffer, jsonString); // Then you need to to deserialize the JSON – this basically means converting it into a representation that Arduino can work with
  JsonObject json = buffer.as<JsonObject>(); // Finally create a new JSON object that you can parse

  // If you look at the Dark Sky API documentation you will see a nicely-formatted example response which makes the hierarchical structure of the JSON more obvious
  // Basically what you are telling it in this next section is 'go to the "[daily]" block, then go to the "[data]" array,
  // then go to the first item in the array [0], and finally go to "[icon]" and return the data it holds

  String weather = json["daily"]["data"][0]["icon"]; // Extract the 'icon' String from the Json Object
  String rain = "rain"; // Then create three new strings to compare it to – if it matches any of these it is raining
  String sleet = "sleet";
  String snow = "snow";

  Serial.println(weather); // This line prints the extracted string to the Serial monitor – use this to check you have a value (e.g. "rain", "sun")
  // If this prints "null" it means something has gone wrong

  // This next boolean will return true if the "weather" string reads "rain", "sleet", or "snow" – remember that == compares two values, and || means 'or'
  // The "?" here is evaluating the expression in the brackets
  // If any of the conditions in the brackets are true, it will return the value to the left of the colon (true),
  // if none of them are true it will return the value to the right of the colon(false)

  bool moveServo = (weather == rain || weather == sleet || weather == snow) ? true : false;

  // You could also write it like this:
  /* bool moveServo;
     if (weather == rain || weather == sleet || weather == snow) {
     moveServo = true;
     } else {
     moveServo = false;
     } */

  if (moveServo)  // If moveServo == true, it is going to rain
  {
    Serial.println("Yes it is going to rain."); // Print a message to the Serial monitor
    moveServoToPos(UMBRELLA_OPEN, 10); // Call the moveServoToPos function – passing in the position that opens the umbrella and a speed of 10
  }
  else // if moveServo == false, it is not going to rain
  {
    Serial.println("No it is not going to rain.");
    moveServoToPos(UMBRELLA_CLOSED, 10); // Call the moveServoToPos function – passing in the position that closes the umbrella and a speed of 10
  }
}
// Move the Servo ---------------------------------
void moveServoToPos(int pos, int sp)  // the two values passed in here tell the Servo what position to move to and how quickly to do it
{
  if (pos < currentServoPos)  // if the 'pos' value you just passed in is less than the last recorded Servo position
  {
    for (int i = currentServoPos; i > pos; i--)  // Use the loop to move the Servo by one degree until it matches the position you just passed in
    {
      myServo.write(i);
      delay(sp); // The delay here controls how quickly the Servo moves to position – remember this is given in milliseconds
    }
  }
  else if (pos > currentServoPos)  // if the 'pos' value you just passed in is greater than the last recorded Servo position
  {
    for (int i = currentServoPos; i < pos; i++)  // Use the loop to move the Servo by one degree until it matches the position you just passed in
    {
      myServo.write(i);
      delay(sp);
    }
  }

  currentServoPos = pos; // update the value for currentServoPos – this keeps track of the Servo's last known position
}
