//   ecaWifiUtilities.h
//
//   A collection of functinos for getting info, setting up and all things arduino WiFi
//
//  created by matthew hamilton on 23/03/2018

#ifndef ECA_WIFI_UTILS
#define ECA_WIFI_UTILS

#include "setupM0WiFi.h"
#include "connectToHanabi.h"

/** Requires that Serial already be started and WiFi already activated.*/
void printWiFiStatus()
{
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);

}

#endif /* ECA_WIFI_UTILS */
