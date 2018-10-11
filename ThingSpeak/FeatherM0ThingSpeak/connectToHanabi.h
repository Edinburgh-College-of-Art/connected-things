/*
   Automated connection to HANABI network. Password needs to be provided (of course)

   Will print out some hand data to serial though this can be stripped out if not
   required.

*/
#ifndef ECA_CONNECT_TO_HANABI
#define ECA_CONNECT_TO_HANABI
#include <SPI.h>
#include <WiFi101.h>
#include "setupM0WiFi.h"
#include "ecaWifiUilities.h"
//==============================================================================
/** Requires that Serial already be started and WiFi already activated.*/
void printWiFiStatus()
{
  if ( WiFi.status() == WL_CONNECTED )
  {
    //===========================================================
    // Print IP Details
    //===========================================================
    Serial.println("Connected to HANABI");
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    Serial.print("Your Local IP is: ");
    Serial.println(IPAddress(WiFi.localIP()));

    Serial.print("NETMASK: ");
    Serial.println(IPAddress(WiFi.subnetMask()));

    Serial.print("GATEWAY: ");
    Serial.println(IPAddress(WiFi.gatewayIP()));

    Serial.print("signal strength (RSSI):");
    Serial.print(WiFi.RSSI());
    Serial.println(" dBm");

    // print where to go in a browser:
    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(IPAddress(WiFi.localIP()));
  }
  else
  {
    Serial.println("WiFi not Connected");
  }
}
//==============================================================================
/**
  Connects adafruit feather M0 to ECA hanabi network

  Contact Matthew for the password.

  @param pass network password
  @return returns the connection status for transparent error checking.

*/
int connectToHanabi(const char pass[])
{
  setupM0WiFi();

  const char ssid[] = "HANABI";    // the name of your network
  const int wifiWait = 3e3;        // Wait time between connection attempts

  //===========================================================
  // Attempt Connection
  //===========================================================
  WiFi.begin(ssid, pass);
  Serial.println();
  Serial.println("Connecting...");
  Serial.println();
  delay(wifiWait);
  int connectAttemptCount = 0;
  while ( WiFi.status() != WL_CONNECTED)
  {
    if (connectAttemptCount > 3)
    {
      Serial.print("Couldn't connect to ");
      Serial.println(ssid);
      Serial.println("Have you registered your MAC address to HANABI?");
      break;
    }
    else
    {
      Serial.print(++connectAttemptCount);
      Serial.println(" Attempt(s)");
      WiFi.begin(ssid);
      delay(wifiWait);
    }
  }

  printWiFiStatus();
  
  return WiFi.status();
}

#endif /* ECA_CONNECT_TO_HANABI */
