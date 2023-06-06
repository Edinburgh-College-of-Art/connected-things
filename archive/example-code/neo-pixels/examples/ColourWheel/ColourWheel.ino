/*
 * Colour Wheel:
 * 
 * Cycle through the available colours of the NeoPixel using a custom function.
 * 
 */
//==========================================================================================
#include <Adafruit_NeoPixel.h>
//==========================================================================================
int pixelNumber  = 14;
int pixelDataPin =  9;
int delayBetweenColourChanges = 100;
//==========================================================================================
uint16_t pixelType = NEO_GRB + NEO_KHZ800; // type should always be this for your NeoPixels
Adafruit_NeoPixel pixelRing = Adafruit_NeoPixel(pixelNumber, pixelDataPin, pixelType);
//==========================================================================================
void setup()
{
  pixelRing.begin();
}
//==========================================================================================
void loop()
{
    for (int i = 0; i < 256; i++)
    {
      pixelRing.fill(colourWheel(i), 0, pixelRing.numPixels());
      pixelRing.show();
      delay(delayBetweenColourChanges);
    }
}

//==========================================================================================
/** 
 * This function cycles through most of the available colours when given a value between 0 and 255 
 * i.e. colourWheel(0) will give a pretty similar colour to colourWheel(255)
 */
uint32_t colourWheel(byte WheelPos)
{
  uint32_t newColour = 0;
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) 
  {
    newColour = Adafruit_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  else if (WheelPos < 170) 
  {
    WheelPos -= 85;
    newColour = Adafruit_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  else 
  {
    WheelPos -= 170;
    newColour = Adafruit_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
  return newColour;
}
