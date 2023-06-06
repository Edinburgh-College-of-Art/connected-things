/*
   Moving Average Filter Example

    Filter out random noise with a moving average filter
*/
#include "MovingAverageFilter.h"
//==============================================================================
MovingAverageFilter filter(20);
//==============================================================================

void setup()
{
  //----------------------------------------------------------------------------
  Serial.begin(115200);
  while (!Serial) {};
  //----------------------------------------------------------------------------
  randomSeed(analogRead(0));
}
//==============================================================================
void loop()
{
  Serial.println(filter.process(random(1000))); // Open the Serial plotter
  delay(50);
}
//==============================================================================
