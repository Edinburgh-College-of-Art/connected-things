// The code on this tab demonstrates how to adjust the brightness of an LED based on a fluctuating variable

void lightLed(float low, float high, float current) {

  // Arduino's map() function is a useful way to map data to an output on your Arduino. It takes 4 values:
  // the value to map; the lowest possible input value; the highest possible input value; the lowest possible output value; the highest possible output value
  // For more info on how it works see: https://www.arduino.cc/reference/en/language/functions/math/map/

  int bright = map(current, low, high, 0, 255);
  // The output values here range from 0 to 255, because this is the maximum range of values that can be written to one of the Arduino's PWM pins using analogWrite()
  Serial.println("LED Brightness: " + bright);

  // Arduino's analogWrite() function is used with the board's Digital PWM pins – you can use it to do things like vary the brightness of an LED
  // For more info on how it works see: https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
  analogWrite(ledPin, bright); // The two values you need to pass in here are teh pin number the LED is connected to and the value you want to write to it

}
