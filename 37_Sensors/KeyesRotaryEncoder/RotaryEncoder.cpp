//===================================================================
#include "RotaryEncoder.h"
//===================================================================

RotaryEncoder::RotaryEncoder(uint8_t pin1, uint8_t pin2, int minimum, int maximum, uint8_t sensitive)
{
  pinA = pin1;
  pinB = pin2;

  min = minimum;
  max = maximum;

  sensitivity = sensitive;
}

void RotaryEncoder::setup()
{
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  if (!Serial)
  {
    Serial.begin (9600);
  }
  previousState = digitalRead(pinA);
}
//===================================================================

void RotaryEncoder::update()
{
  bool currentState = digitalRead(pinA); // Reads the "current" state of the outputA

  if (currentState != previousState) //If previous and current state of outputA are different, a Pulse has occured
  {
    if (digitalRead(pinB) != currentState)  // If outputB state is different outputA state, the encoder is rotating clockwise
    {
      counter ++;
    }
    else
    {
      counter --;
    }
    Serial.print("Position: ");
    Serial.println(getValue());
  }
  previousState = currentState ; //Updates the previous state of outputA with the current state
}
//===================================================================
int RotaryEncoder::getValue()
{
  int out = counter / sensitivity;
  if (out < min)
  {
    out = min;
  }
  if (out > max)
  {
    out = max;
  }
  return out;
}
//===================================================================
