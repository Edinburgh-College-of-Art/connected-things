//================================================================================
#include <driver/source/nmasic.h>
//================================================================================
/**
  Connects adafruit feather M0 to ECA hanabi network

  Contact Matthew for the password.

  @param pass network password
  @return returns the connection status for transparent error checking.

*/
void connectToWifiNetwork(const char ssidName[], const char pass[])
{
  Serial.begin(9600);   // Make sure that the number in the bottom right of the Serial Monitor matches this
  while ( !Serial) {}   // Wait until the Serial port is ready so we don't miss any output
  WiFi.setPins(8, 7, 4, 2); // Setup the WiFi on the Feather boards
  checkFirmware();
  /* Start the WiFi connection */
  Serial.println("Starting...");
  Serial.println("Connecting to WiFi");
  int conn = WiFi.begin(ssidName, pass);

  if ( conn == WL_CONNECTED )
  {
    Serial.println("OK!");
    printWiFiStatus();
  }
  else if ( conn == WL_IDLE_STATUS )
  {
    Serial.println("Idle");
    errorProtocol();
  }
  else
  {
    Serial.println("Unknown response");
     errorProtocol();
  }

}

//================================================================================

/** Print some info about the WiFi */
void printWiFiStatus()
{
  if ( WiFi.status() == WL_CONNECTED )
  {
    //===========================================================
    // Print IP Details
    //===========================================================
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

//================================================================================

/** Checks your firmware and prints some handy info to Serial */
int checkFirmware()
{
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
    Serial.print(mac[5], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.println(mac[0], HEX);

    //===========================================================
  } // end else for Shield Presence

  return WiFi.status();
}
