/*
 * Automated connection to HANABI network. Password needs to be provided (of course)
 * 
 * Will print out some hand data to serial though this can be stripped out if not
 * required.
 *
 */
#ifndef ECA_CONNECT_TO_HANABI
#define ECA_CONNECT_TO_HANABI
#include <SPI.h>
#include <WiFi101.h>
#include "setupM0WiFi.h"

/**
 Connects adafruit feather M0 to ECA hanabi network

 Contact Matthew for the password.

 @param pass network password
 @return returns the connection status for transparent error checking.
 
 */
int connectToHanabi(const char pass[])
{
  setupM0WiFi();

 const char ssid[] = "HANABI";     // the name of your network
 const int wifiWait = 3e3;        // Wait time between connection attempts
 int status = WL_IDLE_STATUS;     // the Wifi radio's status
 
 
 //===========================================================
 // Attempt Connection
 //===========================================================
 
 status = WiFi.begin(ssid, pass);
 Serial.println(); 
 Serial.println("Connecting..."); 
 Serial.println(); 
 delay(wifiWait);
 int connectAttemptCount = 0;
 while ( status != WL_CONNECTED) 
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
        status = WiFi.begin(ssid);
        delay(wifiWait);
      }
 } 

  if ( status == WL_CONNECTED ) 
  {
    //===========================================================
    // Print IP Details
    //===========================================================
    Serial.println("Connected to HANABI");
    Serial.print("Your IP is: ");
    IPAddress ip = WiFi.localIP();
    Serial.println(ip);
    IPAddress subnet = WiFi.subnetMask();
    Serial.print("NETMASK: ");
    Serial.println(subnet);
    IPAddress gateway= WiFi.gatewayIP();
    Serial.print("GATEWAY: ");
    Serial.println(gateway);;
  }
  return status; 
}

#endif /* ECA_CONNECT_TO_HANABI */
