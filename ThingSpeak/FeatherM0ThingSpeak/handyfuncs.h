/*
 * handyfuncs
 * 
 * A selection of punchy and helpful little functions for arduino
 *
 */
#ifndef ECA_HANDY_FUNCS
#define ECA_HANDY_FUNCS
//==============================================================================


/**
 checks the time between calls and flip the state if it is greater than the given interval

 @param interval in milliseconds
 @param pinNumber output pin number
 @return returns the pin state if the interval has not passed yet or the opposite state
         if it has.
 */

int checkInterval (const unsigned long interval, const int pinNumber)
{
    const unsigned long currentTime = millis();
    static unsigned long previousTime = 0; // only zero on first call as it is 'static'
    
    int stateResult = 0;
    if (currentTime - previousTime >= interval)
    {
        previousTime = currentTime;
        
        if (digitalRead (pinNumber) == LOW)
        {
            stateResult = HIGH;
        }
        else
        {
            stateResult = LOW;
        }
    }
    else
    {
        stateResult = digitalRead (pinNumber);
    }
    return stateResult;
}

//==============================================================================

/**
 check analog pin value if time between calls is greater than interval

 @param interval milliseconds
 @param pinNumber input pin
 */
void checkAnalogPin (const unsigned long interval, const int pinNumber)
{
    const unsigned long currentTime = millis();
    static unsigned long prevTime = 0; // only zero on first call as it is 'static'
    int stateResult = 0;
    if (currentTime - prevTime >= interval)
    {
        prevTime = currentTime;
        float pinValue = (analogRead(pinNumber)/1023.f)*1000;
        Serial.println(pinValue);
    }
}

//==============================================================================

/**
 Ramp voltage between min and max voltage on A0 pin: adafruit feather m0
 

 @param steps number of voltage steps between min and max voltage. 
              Maximum number of steps is 255 for full range. More can be stated
              but with no effect.
 @param minV min voltage
 @param maxV max voltage
 @param microDelay delay between voltage steps
 */
void ramp(int steps, float minV, float maxV, int microDelay)
{
    const int voltageMinInt = 77*minV;
    const int voltageMaxInt = 77*maxV;
    for (int j = 0; j < steps; ++j)
    {
        int voltInt = map (j, 0, steps, voltageMinInt, voltageMaxInt);
        analogWrite(A0,voltInt);
        delayMicroseconds(microDelay);
    }
    
    for (int j = stepCount; j > 0; --j)
    {
        int voltInt = map (j, 0, steps, voltageMinInt, voltageMaxInt);
        analogWrite(A0, voltInt);
        delayMicroseconds(microDelay);
    }
}

#endif /* ECA_HANDY_FUNCS */
