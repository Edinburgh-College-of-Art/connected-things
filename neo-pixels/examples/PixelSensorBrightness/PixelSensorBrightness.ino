/*
   PixelSensorBrightness

   Control the brightness of leds with an ultrasound sensor if the distance detected is between 10 cm and 100 cm

*/
//==========================================================================================
#include <Adafruit_NeoPixel.h>
#include <Ultrasonic.h>
//==========================================================================================
int pixelNumber  = 14;
int pixelDataPin =  9;
uint32_t pixelColour = 0xFFFFFF; // RGB Value
int brightness = 0;
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
  //  pixelRing.show();
  Serial.begin(9600);
}
//==========================================================================================
void loop()
{
  int distance = ultrasonic.read();
  
    brightness = constrain(map(distance, 10, 100, 1, 255), 1, 255);
  
  Serial.println(brightness);
  pixelRing.setBrightness(brightness);
  pixelRing.show();
  delay(40);
}
//==========================================================================================
