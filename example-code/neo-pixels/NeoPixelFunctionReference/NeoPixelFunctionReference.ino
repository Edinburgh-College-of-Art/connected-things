/*
   Reference for NeoPixel Library Functions
*/
#include <Adafruit_NeoPixel.h>
//==========================================================================================
#define PIXEL_PIN    6    // Digital IO pin connected to the NeoPixels.
#define PIXEL_COUNT 16
//==========================================================================================
Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  // Void
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
//  strip.setPin(/*uint8_t p*/);
//  strip.setPixelColor(/*uint16_t n, uint8_t r, uint8_t g, uint8_t b*/);
//  strip.setPixelColor(/*uint16_t n, uint8_t r, uint8_t g, uint8_t b, uint8_t w*/);
//  strip.setPixelColor(/*uint16_t n, uint32_t c*/);
//  strip.fill(/*uint32_t c=0, uint16_t first=0, uint16_t count=0*/);
//  strip.setBrightness(/*uint8_t*/);
//  strip.clear();
//  strip.updateLength(/*uint16_t n*/);
//  strip.updateType(/*neoPixelType t*/);
//
//  // uint8_t
//  strip.getPixels();
//  strip.getBrightness();
//  strip.sine8(/*uint8_t*/);
//  strip.gamma8(/*uint8_t*/);
//
//  // int8_t
//  strip.getPin();
//
//  // uint16_t
//  strip.numPixels();
//
//  //  static uint32_t
//  strip.Color(/*uint8_t r, uint8_t g, uint8_t b*/);
//  strip.Color(/*uint8_t r, uint8_t g, uint8_t b, uint8_t w*/);
//
//  //  uint32_t
//  strip.getPixelColor(/*uint16_t n*/);
//
//  //  inline bool
//  strip.canShow();
}

void loop()
{

}
