/*
   get the weather from the DarkSkyAPI
*/
#include <WiFi101.h>
#include <Servo.h>
#include <ArduinoJson.h>
//----------------------------------------------------------------------------
String yourApiKey = "";
String host = "api.darksky.net";
String url = "/forecast/" + yourApiKey + "/55.94100,-3.20356,1578665400?exclude=minutely,flags,hourly,currently,alerts";
//----------------------------------------------------------------------------
// WiFi Details
const char* ssid     = "SSID";
const char* password = "PASSWORD";
WiFiSSLClient client;
//----------------------------------------------------------------------------
void setup()
{
  connectToWifiNetwork(ssid, password);
  //----------------------------------------------------------------------------
  // connect to API
  if (client.connect(host.c_str(), 443))
  {
    client.println("GET " + url + " HTTP/1.1");
    client.println("Host: " + host);
    client.println("Connection: close");
    client.println();
  }
  //----------------------------------------------------------------------------
  // Read json data
  while (client.connected())
  {
    String line = client.readStringUntil('\n');
    if (line == "\r")
      break;
  }
  String jsonString = client.readString();
  //----------------------------------------------------------------------------
  // Read json data to object
  DynamicJsonDocument buffer(2048);
  deserializeJson(buffer, jsonString);
  JsonObject json = buffer.as<JsonObject>();
  //----------------------------------------------------------------------------
  // find out if its raning
  String weather = json["daily"]["data"][0]["icon"];
  String rain  = "rain";
  String sleet = "sleet";
  String snow  = "snow";

  bool moveServo = (weather == rain ||
                    weather == sleet ||
                    weather == snow) ? true : false;

  if (moveServo)
  {
    // move Servo function
  }

}

void loop()
{


}
