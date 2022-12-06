/*
   Feather M0 Air Quality without timers

  Looking into the example code for the air quality sensor it is a little convoluted for no
  real reason. Here is a slightly simplified version of what is going on.
*/
//----------------------------------------------------------------------------
#include "AirQuality.h"
//----------------------------------------------------------------------------
AirQuality airqualitysensor;
unsigned long previousMillis = 0;

void setup()
{  
  Serial.begin(9600);
  while (!Serial) delay(10);
  Serial.println("Starting...");  
}
//----------------------------------------------------------------------------
void loop()
{
  getAirQuality();
}
//----------------------------------------------------------------------------
