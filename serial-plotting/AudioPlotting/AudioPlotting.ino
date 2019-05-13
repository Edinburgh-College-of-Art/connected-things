/*
   Read a microphone print out the audio signal, the filtered signal
   and a reference line
*/
#include "MovingAverageFilter.h"
//========================================================================
const unsigned long baud = 230400;
unsigned int bytesPerSec = baud / 10;
unsigned int numberSize = sizeof(int); // how many bytes is a number
unsigned int minMicroDelay = 1e6 / (bytesPerSec * numberSize); // the shortest we can wait before sending the next message
//========================================================================
volatile int micVal = 0; // variables changed by timer are marked as volatile
volatile int filteredMic = 0; // variables changed by timer are marked as volatile
//========================================================================
unsigned int winSize = 30; // size of averaging window
MovingAverageFilter filter(winSize);
//========================================================================
int axmin = 0;
int axmax = 1024;
//========================================================================
void setup()
{
  Serial.begin(baud);
  while (!Serial) {}  // Wait to open serial monitor before continuing
}

//========================================================================

void loop()
{
  micVal = analogRead(A0);
  filteredMic = filter.process(micVal);
  //--------------------------------------------------------------------------------------------
  Serial.print(micVal); // blue
  delayMicroseconds(minMicroDelay);
  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(filter.process(micVal)); // (red)
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
  Serial.println(512); // centre line (green)
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
}
