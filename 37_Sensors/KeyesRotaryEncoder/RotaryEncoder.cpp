//===================================================================
#include "RotaryEncoder.h"
//===================================================================

RotaryEncoder::RotaryEncoder(uint8_t pin1, uint8_t pin2, uint8_t butPin, int minimum, int maximum, uint8_t sensitive)
{
  pinA = pin1;
  pinB = pin2;
  buttonPin = butPin;

  min = minimum;
  max = maximum;

  sensitivity = sensitive;
}

void RotaryEncoder::setup()
{
  pinMode (pinA, INPUT);
  pinMode (pinB, INPUT);
  pinMode (buttonPin, INPUT);
  
  if (!Serial)
  {
    Serial.begin (9600);
  }
  previousState = digitalRead(pinA);
}
//===================================================================

void RotaryEncoder::update()
{
  bool currentState = digitalRead(pinA);

  if (currentState != previousState)
  {
    if (digitalRead(pinB) != currentState)
    {
      counter ++;
      if (counter > max * sensitivity)
      {
        counter = max * sensitivity;
      }
    }
    else
    {
      counter --;
      if (counter < min * sensitivity)
      {
        counter = min * sensitivity;
      }
    }
    Serial.print("counter: ");
    Serial.println(counter);
    Serial.print("Value: ");
    Serial.println(clamp(counter / sensitivity));
  }
  previousState = currentState ;
}
//===================================================================
int RotaryEncoder::getValue()
{
  return clamp(counter / sensitivity);
}
//===================================================================
int RotaryEncoder::clamp(int input)
{
  int out = input;
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
bool RotaryEncoder::isButtonPressed()
{
  return digitalRead(buttonPin);
}
