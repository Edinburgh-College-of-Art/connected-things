/*
   Feather M0 Air Quality without timers

  Looking into the example code for the air quality sensor it is a little convoluted for no
  real reason. Here is a slightly simplified version of what is going on.
*/
//==============================================================================
#include "AirQuality.h"
//==============================================================================
AirQuality airqualitysensor;
//==============================================================================
// Globals
bool ledState = false;
const uint8_t ledPin = A5;
unsigned long previousMillis = 0; // will store last time reading was taken
const long readInterval = 2000;   // interval to take readings
//==============================================================================
void setup()
{
  //----------------------------------------------------------------------------
  Serial.begin(9600);
  while (!Serial) {};
  Serial.println("Starting...");
  //----------------------------------------------------------------------------
  airqualitysensor.init(A0);
  //----------------------------------------------------------------------------
}
//==============================================================================
void loop()
{
  getAirQuality();
}
//==============================================================================
