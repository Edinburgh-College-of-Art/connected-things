/*
   Plot a random number and the average
*/
//====================================================================================
#include "MovingAverageFilter.h"
//====================================================================================
const unsigned long baud = 9600;
unsigned int bytesPerSec = baud / 10;
unsigned int numberSize = sizeof(int); // how many bytes is a number
unsigned int minMicroDelay = 1e6 / (bytesPerSec * numberSize); // the shortest we can wait before sending the next message
//====================================================================================
unsigned int winSize = 20; // size of averaging window
MovingAverageFilter filter(winSize); 
//====================================================================================

void setup()
{
  Serial.begin(baud);
  while (!Serial) {}  // Wait to open serial monitor before continuing
  randomSeed(analogRead(0));
}

//====================================================================================

void loop()
{
  int x = random(1024);
  //--------------------------------------------------------------------------------------------
  Serial.print(random(300,700)); // blue
  delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

  Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(filter.process(x)); // averaged random noise (red)
  delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

  Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(1024); // blue
  delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

  Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
  delayMicroseconds(minMicroDelay);

  Serial.print(0); // blue
  delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

  Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
  delayMicroseconds(minMicroDelay);
  Serial.println(512); // centre line (green)
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
}
