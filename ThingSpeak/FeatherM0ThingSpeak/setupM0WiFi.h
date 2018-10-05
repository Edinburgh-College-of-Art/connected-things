/*
* Adafruit Feather M0 WiFi Check
*
*  Code checks sets the correct pins for WiFi functionality
*  as well as reporting back on firmware and MAC address
*
*  Includes are relative pathname for Arduino IDE
*
*
*/

#ifndef ECA_SETUP_M0_WIFI
#define ECA_SETUP_M0_WIFI
#include <SPI.h>
#include <WiFi101.h>
#include <driver/source/nmasic.h>

/**
 * This function can basically replace any arduino  wifi.status
 * initialisation code up to and including a if (WiFi.status() == WL_NO_SHIELD)
 * line
 *
 * @returns WiFi.status() for transparent error checking
 */
int setupM0WiFi()
{

  WiFi.setPins(8,7,4,2);// feather m0 WiFi pins
  Serial.begin(9600);
  while (!Serial) {}    // wait for serial port to connect

  //===========================================================
  // Print firmware version on the shield
  //===========================================================
  Serial.println("WiFi101 firmware check.");
  Serial.println();
  Serial.print("WiFi101 shield: ");
  if (WiFi.status() == WL_NO_SHIELD)   // Check for the presence of the shield
  {
    Serial.println("NOT PRESENT");
  }
  else
  {
    Serial.println("DETECTED");
    //===========================================================
    // Print firmware version on the shield
    //===========================================================
    String fv = WiFi.firmwareVersion();
    Serial.print("Firmware version installed: ");
    Serial.println(fv);

    //===========================================================
    // Check Latest Firmware
    //===========================================================
    String latestFv;
    if (REV(GET_CHIPID()) >= REV_3A0)
    {
      // model B
      latestFv = WIFI_FIRMWARE_LATEST_MODEL_B;
    }
    else
    {
      // model A
      latestFv = WIFI_FIRMWARE_LATEST_MODEL_A;
    }

    Serial.print("Latest firmware version available : ");
    Serial.println(latestFv);
    Serial.println();

    if (fv == latestFv)
    {
      Serial.println("Check result: PASSED");
    }
    else
    {
      Serial.println("Check result: NOT PASSED");
      Serial.println(" - The firmware version on the shield do not match the");
      Serial.println("   version required by the library, you may experience");
      Serial.println("   issues or failures.");
    }
    Serial.println();

    //===========================================================
    // Print MAC
    //===========================================================
    byte mac[6];
    WiFi.macAddress(mac);
    Serial.print("MAC: ");
    Serial.print(mac[5],HEX);
    Serial.print(":");
    Serial.print(mac[4],HEX);
    Serial.print(":");
    Serial.print(mac[3],HEX);
    Serial.print(":");
    Serial.print(mac[2],HEX);
    Serial.print(":");
    Serial.print(mac[1],HEX);
    Serial.print(":");
    Serial.println(mac[0],HEX);

    //===========================================================
  } // end else for Shield Presence

  return WiFi.status();
}

#endif /* ECA_SETUP_M0_WIFI */
