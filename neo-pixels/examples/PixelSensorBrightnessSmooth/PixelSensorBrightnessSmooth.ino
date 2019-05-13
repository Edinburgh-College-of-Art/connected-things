/*
  Same as PixelSensorBrightness except the transition between brightness values is now smoother.
*/
//==========================================================================================
#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>
//==========================================================================================
int pixelNumber  = 14;
int pixelDataPin =  9;
uint32_t pixelColour = 0xFFFFFF; // RGB Value
int currentBrightness = 0;
int targetBrightness;
//==========================================================================================
uint16_t pixelType = NEO_GRB + NEO_KHZ800; // type should always be this for your NeoPixels
Adafruit_NeoPixel pixelRing = Adafruit_NeoPixel(pixelNumber, pixelDataPin, pixelType);
//==========================================================================================
int trigPin = 12;
int echoPin = 13;
Ultrasonic ultrasonic(trigPin, echoPin);
//==========================================================================================
void setup()
{
  pixelRing.begin();
  pixelRing.fill(pixelColour, 0, pixelRing.numPixels());
}
//==========================================================================================
void loop()
{
  int distance = ultrasonic.read();

  if (distance > 5 && distance < 100)
  {
    targetBrightness = constrain(map(distance, 10, 90, 0, 255), 1, 255);
  }
  
  if ((targetBrightness - currentBrightness) > 0)
  {
    currentBrightness++;
  }
  else if ((targetBrightness - currentBrightness) < 0)
  {
    currentBrightness--;
  }

  if (targetBrightness != currentBrightness)
  {    
    pixelRing.setBrightness(currentBrightness);
    pixelRing.show();    
  }
  delay(10);
}


//==========================================================================================
