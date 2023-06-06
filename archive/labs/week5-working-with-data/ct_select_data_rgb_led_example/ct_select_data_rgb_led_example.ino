// This example demonstrates how to download JSON data from an API, parse values from the JSON,
// and use these values to control the colour of an RGB LED
// NOTE: To use this sketch, you will need to replace the values for ssid, password, and darkSkyApiKey (on checkWeather tab) with your own values

// Libraries -----------------------------------
#include <WiFiNINA.h> // Use this WiFi library for the Nano 33 IoT board
// #include <WiFi101.h> // Use this WiFi library for the Feather M0
#include <ArduinoJson.h> // You will need this library to work with JSON


// WiFi Network -------------------------------
const char* ssid = "your_ssid"; // Replace with the name of your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network


// WiFiClients --------------------------------
WiFiClient client; // create a new WiFiClient - you need this to create an unsecured connection to an API
WiFiSSLClient sslClient; // create a new WiFiSSLCleint – you will need this to create a secure connection to an API


// RGB LED ----------------------------------------
const int redLed = 5;// create an int to hold the number of the pin red element of the LED is attached to
const int greenLed = 2; // do the same for the green and blue elements
const int blueLed = 3;
// For this example, we will need to use PWM pins – these are indicated on the Arduino by a tilde ( ~ )


// Timer --------------------------------------
// Instead of using a delay, we are going to write a simple timer to control when Arduino makes an API call
const long timer = 600000; // create a long to hold the time (in milliseconds) you want to elapse between API calls (600000ms = 10mins)
long pTime = 0; // create a long to hold the time (in milliseconds) of your last API call


// Setup --------------------------------------
void setup()
{
  Serial.begin(9600); // open the Serial port and sent the baud rate (communication speed)
  while (!Serial)
  {} // do nothing until the Serial port is ready

  pinMode(redLed, OUTPUT); // Set your LED pins to be OUTPUTS
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  connectToWiFi(ssid, password); // connect to the local WiFi network
  checkWeather(); // call the function that gets the weather forecast from Dark Sky (on checkWeather tab)

}
// Loop ---------------------------------------
void loop()
{
  // millis() returns the time in milliseconds since the program first started running on the Arduino, see https://www.arduino.cc/reference/en/language/functions/time/millis/ for more info
  if (millis() > pTime + timer)  // If the current time is greater than the combined value of millis() at the last time the API was called and that of the timer
  {
    pTime = millis(); // Set pTime to equal the current value of millis() - this is keeping track of when the last API call was made
    checkWeather(); // Call the checkWeather function
  }

}
