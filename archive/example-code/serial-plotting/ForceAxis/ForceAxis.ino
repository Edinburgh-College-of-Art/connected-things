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
int axmin = 0;
int axmax = 1024;
void setup()
{
  Serial.begin(baud);
  while (!Serial) {}  // Wait to open serial monitor before continuing
  randomSeed(analogRead(0));
}

//====================================================================================

void loop()
{
  int x = random(300, 700);
  //--------------------------------------------------------------------------------------------
  Serial.print(x);
  delayMicroseconds(minMicroDelay);
  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(filter.process(x));
  delayMicroseconds(minMicroDelay);
  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(axmax);
  delayMicroseconds(minMicroDelay);
  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(axmin);
  delayMicroseconds(minMicroDelay);
  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.println(512);
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
}
