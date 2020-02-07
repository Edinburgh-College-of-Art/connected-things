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
const char* ssid = "SSID";          // replace these with the name and password for your local wi-fi network
const char* password = "PASSWORD";
//---------------------------------------------------------------------------------------------------------------------------------------
// API
String host = "api.carbonintensity.org.uk";
String url = "/intensity/date";            

//---------------------------------------------------------------------------------------------------------------------------------------
// WiFi Client
WiFiSSLClient sslClient;  // HTTPS
WiFiClient client;        // HTTP
char httpResponse[10000]; // If you are getting responses larger that 10kB, use another request.
//---------------------------------------------------------------------------------------------------------------------------------------
// Timer 
unsigned long updateTimer = 300000;
//---------------------------------------------------------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); 
  while (!Serial) {} // This line is blocking, remove it when you are finished
  
  connectToWifi(ssid, password);
    
  JsonObject json = makeAPIcall(host, url, sslClient, 443);
  
  String someData = json["data"][0]["intensity"]["forecast"]; // This will change depending on the API of course
 
  Serial.println("\n\nSome Data: ");Serial.println(someData);
  Serial.println("Now Get to Work!");
  haltFirmware();
}

//---------------------------------------------------------------------------------------------------------------------------------------

void loop()
{

}
