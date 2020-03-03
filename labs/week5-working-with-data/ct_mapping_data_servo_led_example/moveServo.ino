void moveServo(float low, float high, float current)
{
  // Arduino's map() function is a useful way to map data to an output on your Arduino. It takes 4 values:
  // the value to map; the lowest possible input value; the highest possible input value; the lowest possible output value; the highest possible output value
  // For more info on how it works see: https://www.arduino.cc/reference/en/language/functions/math/map/

  int pos = map(current, low, high, 0, 180);
  // The output values here range from 0 to 180, because this is the maximum rotational range of the Servo
  Serial.println("Servo position: " + pos);

  if (pos < currentServoPos)  // If the position we want to move the servo to is less than its last recorded position
  {
    for (int i = currentServoPos; i > pos; i--)  // Use the loop to move the servo by one degree until it reaches the position calculated above
    {
      myServo.write(i);
      delay(10); // This controls how quicly the servo moves into position – making this smaller will make it move faster; making it bigger will make it move slower
    }
  }
  else if (pos > currentServoPos)  // If the position we want to move the servo to is greater than its last recorded position
  {
    for (int i = currentServoPos; i < pos; i++)
    {
      myServo.write(i);
      delay(10);
    }
  }

  currentServoPos = pos; // Update the value for currentServoPos to keep track of the current position of the servo
  Serial.println("Current Servo Position: " + currentServoPos);

}
