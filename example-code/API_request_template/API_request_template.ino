/*
   What is this called?

   What does it do?

   Who wrote it? and when?

   What equipment do I need

   What pins are connected to what?

   | Arduino Pin | Device pin |
   | ----------- | ---------- |
   | 0           |            |
   | 1           |            |
   | 2           |            |
   | 3           |            |
   | 5V          |            |
   | GND         |            |

*/

//---------------------------------------------------------------------------------------------------------------------------------------
// Libraries -----------------------
#ifdef ARDUINO_SAMD_ZERO
#pragma message "You are Using the Feather M0"
#endif

#ifdef ARDUINO_SAMD_NANO_33_IOT
#pragma message "You are Using the IoT Nano 33"
#endif

#define SOCKET_BUFFER_MTU            (16u)
#define SOCKET_BUFFER_UDP_SIZE          (SOCKET_BUFFER_UDP_HEADER_SIZE + 64u)
#define SOCKET_BUFFER_TCP_SIZE          (64u)

#include <WiFi101.h> // Use this WiFi library if running this sketch on Feather M0 board
#include <ArduinoJson.h> // This library is for handling JSON Data in Arduino
//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Connection -----------------------
const char* ssid = "HANABI"; // If you are not at ECA, replace these with the name and password for your local wi-fi network
const char* password = "lowernorwood";
//---------------------------------------------------------------------------------------------------------------------------------------
// Carbon Intensity API --------------------------
String host = "api.carbonintensity.org.uk"; // Create a string to hold the name of the host you are connecting to
String url = "/intensity/date"; // create a string to hold your HTTP request URL
// The final part of the URL (?exclude...) is telling Dark Sky to exclude the named data blocks from the API response
//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Client --------------------------
WiFiSSLClient client; // Create a new WiFi SSL Client – this will give us a secure connection (https) to Dark Sky through port 443
char httpResponse[8425];

//---------------------------------------------------------------------------------------------------------------------------------------
// Timer --------------------------------
long timer = 300000; // We will use this long in the main loop to control how often Arduino sends HTTP Requests to the Carbon Intensity API
// The value you put here is the time in milliseconds you want to wait between API calls – in this case 300000 ms = 5 minutes

//---------------------------------------------------------------------------------------------------------------------------------------
// Setup -------------------------------
void setup()
{
  connectToWifi(ssid, password); // Call the function that connects the Arduino to WiFi – passing in the values for ssid and password created above
  Serial.println("https://" + host + url); // I have included this line to help you test your HTTP request
  // This will print your full HTTP request URL to the Serial port – if you copy and paste it into your web browser you can check if your request is working correctly
  JsonObject json = makeAPIcall(host, url); // call the checkCO2 function to get a forecast from Dark Sky
  String t = json["data"][0]["intensity"]["forecast"];
  Serial.println(t);
}

//---------------------------------------------------------------------------------------------------------------------------------------

void loop()
{

  delay(timer); // do nothing for the next five minutes – make sure you include this or you will very quickly hit your rate limit
}
