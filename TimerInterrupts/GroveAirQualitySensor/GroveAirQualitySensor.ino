/*
   Feather M0 Timer Interrupt

   This example demonstrates the usage of timer interrupts on the Feather M0

   It is essentially a massively over engineered way to blink an LED on and off.
   The real beauty is in the fact that this is the most guarenteed way to regularly
   perform an operation at a set interval.

   If you want to sample data, or output data at a sampling rate (e.g. audio)
   then this is where you would start

   If you want to change what happens at the interrupt, look at TC3_Handler

   You should not need to look at startTimer or setTimerFrequency unless
   you want to understand the M0 architecture better.

*/
//==============================================================================
#include <AirQuality.h>
//==============================================================================
AirQuality airqualitysensor;
int current_quality =-1;
//==============================================================================
// Globals
bool ledState = false;
const uint8_t ledPin = A5;
//==============================================================================
void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  //----------------------------------------------------------------------------
  Serial.begin(9600);
  while(!Serial){};
  Serial.println("Starting..."); 
  //----------------------------------------------------------------------------
  airqualitysensor.init(A0);
  //----------------------------------------------------------------------------
  startTimer(1600000); // timer frequency 16MHz
  //----------------------------------------------------------------------------
}
//==============================================================================
void loop()
{
  current_quality = airqualitysensor.slope();
  if (current_quality >= 0)// if a valid data returned.
  {
    if (current_quality == 0)
      Serial.println("High pollution! Force signal active");
    else if (current_quality == 1)
      Serial.println("High pollution!");
    else if (current_quality == 2)
      Serial.println("Low pollution!");
    else if (current_quality == 3)
      Serial.println("Fresh air");
  }
}
//==============================================================================
