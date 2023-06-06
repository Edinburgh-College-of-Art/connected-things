/*
   Light up n number of pixels based on sensor reading between 10cm and 50cm
*/
//==========================================================================================
#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>
//==========================================================================================
int pixelNumber  = 14;
int pixelDataPin =  9;
uint32_t pixelColour = 0xAA0000; // RGB Value
int delayBetweenChanges = 100;
uint8_t brightness = 0;
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
}
//==========================================================================================
void loop()
{
  int distance = ultrasonic.read();
  int ledCount = constrain(map(distance, 10, 50, 0, pixelRing.numPixels()), 0, pixelRing.numPixels());
  pixelRing.clear();
  for (int i = 0; i < ledCount; i++)
  {
    pixelRing.setPixelColor(i, 0);
    pixelRing.setPixelColor(i, pixelColour);
  }
  pixelRing.show();
  delay(50);
}
//==========================================================================================
