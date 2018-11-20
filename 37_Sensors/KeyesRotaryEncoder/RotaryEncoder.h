/*
   Class for Keyes Rotary Encoder
*/
#include <Arduino.h>
//===================================================================
class RotaryEncoder
{
  public:
    //===================================================================
    // Methods
    //===================================================================
    RotaryEncoder(uint8_t pin1, uint8_t pin2, int minimum, int maximum, uint8_t sensitive);
    //===================================================================
    void setup();
    //===================================================================
    // detect change in state of encoder
    void update();
    //===================================================================
    // return the current value based sensitivity
    int getValue();
    //===================================================================
  private:
    int counter = 0;
    bool previousState;
    uint8_t pinA;
    uint8_t pinB;
    uint8_t sensitivity;
    int min;
    int max;
};
//===================================================================
