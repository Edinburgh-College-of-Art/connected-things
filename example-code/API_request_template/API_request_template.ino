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

  Do you need to add any certificates?
*/

//---------------------------------------------------------------------------------------------------------------------------------------
// Libraries
#ifdef ARDUINO_SAMD_ZERO
#pragma message "You are Using the Feather M0"
#include <WiFi101.h> 
#endif

#ifdef ARDUINO_SAMD_NANO_33_IOT
#pragma message "You are Using the IoT Nano 33"
#include <WiFiNINA.h>
#endif

#include <ArduinoJson.h>
//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Connection
const char* ssid = "SSID";          // If you are not at ECA, replace these with the name and password for your local wi-fi network
const char* password = "PASSWORD";
//---------------------------------------------------------------------------------------------------------------------------------------
// API
String host = "api.carbonintensity.org.uk"; // Create a string to hold the name of the host you are connecting to
String url = "/intensity/date";             // create a string to hold your HTTP request URL

//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Client
WiFiSSLClient sslClient;     // Create a new WiFi SSL Client – this will give us a secure connection (https) to Dark Sky through port 443
WiFiClient client;     // Create a new WiFi SSL Client – this will give us a secure connection (https) to Dark Sky through port 443
char httpResponse[10000]; // If you are getting responses larger that 10kB, may be use another request.
//---------------------------------------------------------------------------------------------------------------------------------------
// Timer 
unsigned long updateTimer = 300000;
//---------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); 
  while (!Serial) {} // This line is blocking, remove it when you are finished
  
  connectToWifi(ssid, password);
    
  JsonObject json = makeSSLAPIcall(host, url); // HTTPS
//  JsonObject json = makeAPIcall(host, url);    // HTTP
  
  String someData = json["data"][0]["intensity"]["forecast"]; // This will change depending on the API of course
  Serial.println(someData);
  Serial.println("Now Get to Work!");
}

//---------------------------------------------------------------------------------------------------------------------------------------

void loop()
{

}
