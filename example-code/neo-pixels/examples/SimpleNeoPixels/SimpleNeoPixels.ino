/*
  Light up all pixels 1 by 1 a single colour
*/
//==========================================================================================
#include <Adafruit_NeoPixel.h>
//==========================================================================================
int pixelNumber  = 14;
int pixelDataPin =  9;
uint32_t pixelColour = 0x009A00; // RGB Value
int delayBetweenChanges = 100;
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
  pixelRing.clear();
  for (int i = 0; i < pixelRing.numPixels(); i++)
  {
    pixelRing.setPixelColor(i, pixelColour);
    pixelRing.show();
    delay(delayBetweenChanges);
  }
}
//==========================================================================================
