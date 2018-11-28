/*
  Read a microphone at a fixed sampling rate and print out the audio signal, the filtered signal
  and a reference line
*/
#include "MovingAverageFilter.h"
//========================================================================
const uint16_t sampleRate = 44100;
//========================================================================
const unsigned long baud = 9600;
unsigned int bytesPerSec = baud / 10;
unsigned int numberSize = sizeof(int); // how many bytes is a number
unsigned int minMicroDelay = 1e6 / (bytesPerSec * numberSize); // the shortest we can wait before sending the next message
//========================================================================
volatile int micVal = 0; // variables changed by timer are marked as volatile
volatile int filteredMic = 0; // variables changed by timer are marked as volatile
//========================================================================
unsigned int winSize = 20; // size of averaging window
MovingAverageFilter filter(winSize);
//========================================================================
void setup()
{
  Serial.begin(9600);
  while (!Serial) {}  // Wait to open serial monitor before continuing
  InitTimer();
}

//========================================================================

void loop()
{
  //--------------------------------------------------------------------------------------------
  Serial.print(micVal); // blue
  delayMicroseconds(minMicroDelay);

  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.print(filteredMic); // (red)
  delayMicroseconds(minMicroDelay);

  Serial.print(",");
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.println(512); // centre line (green)
  delayMicroseconds(minMicroDelay);
}

//========================================================================

// Timer calback
// This is what happens every sampleRate times per second
ISR(TIMER1_COMPA_vect)
{
  micVal = analogRead(A1);
  filteredMic = filter.process(micVal);
}

//========================================================================
