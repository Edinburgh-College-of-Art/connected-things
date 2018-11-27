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
    RotaryEncoder(uint8_t clk, uint8_t dat, uint8_t butPin, int minimum, int maximum, uint8_t sensitive);
    //===================================================================
    void setup();
    //===================================================================
    // detect change in state of encoder
    void update();
    //===================================================================
    // return the current value based sensitivity
    int getValue();
    //===================================================================
    // clamp a value to the given min and max of the object
    int clamp(int input);
    //===================================================================
    bool buttonPressed();
  private:
    int counter = 0;
    bool previousState;
    uint8_t pinA;
    uint8_t pinB;
    uint8_t buttonPin;
    uint8_t sensitivity;
    int min;
    int max;
};
//===================================================================
