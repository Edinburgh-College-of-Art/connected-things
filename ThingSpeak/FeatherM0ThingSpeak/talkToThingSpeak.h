//   ecaWifiUtilities.h
//
//   A collection of functinos for getting info, setting up and all things arduino WiFi
//
//  created by matthew hamilton on 23/03/2018
//===========================================================================
#ifndef ECA_THING_SPEAK
#define ECA_THING_SPEAK
//===========================================================================
#include <WiFi101.h>
//===========================================================================
void sendDataToThingSpeak(String data[], int numberOfFields, String channelAPIKey)
{
    WiFiClient client;
    String dataString = "";
    
    for (int i = 0; i < numberOfFields; ++i)
        dataString += "&field" + String(i + 1) + "=" + data[i];
    
    Serial.println(dataString);
    char thingSpeakAddress[] = "api.thingspeak.com";
    
    Serial.println("connecting to ThingSpeak ...");
    if (client.connect(thingSpeakAddress, 80))
    {
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: " + channelAPIKey + "\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(dataString.length());
        client.print("\n\n");
        client.print(dataString);
    }
    else
    {
        Serial.println("Could Not Connect\n");
    }
    client.stop();
}
//===========================================================================
#endif /* ECA_THING_SPEAK */
