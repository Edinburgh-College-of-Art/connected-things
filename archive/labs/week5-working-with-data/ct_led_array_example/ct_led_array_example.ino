// This code demonstrates how to cycle through an Array and blink 3 LEDs in sequence
// An Array is essentially a list of variables that can be accessed with an index number
// For more info see: https://www.arduino.cc/reference/en/language/variables/data-types/array/

int ledPins [] = {2, 3, 5}; // Create a new array of ints and input the pin numbers for your LEDs

void setup()
{
  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial) {} // Wait until the Serial port is ready

  // An array element is accessed using the following notation arrayName[index]
  // In this example ledPins[1] = 3;
  for (int i = 0; i < 3; i++) // Use a for loop to cycle through your array
  {
    pinMode(ledPins[i], OUTPUT); // Set the pinMode for each of the pins you're using to OUTPUT
  }

}
void loop()
{
  for (int i = 0; i < 3; i++) // Use a for loop to cycle through your array
  {
    Serial.println(i); // Print the current value of i to the Serial so you can see what's going on
    digitalWrite(ledPins[i], HIGH); // Turn the specified LED on
    delay(500); // Wait for 500 milliseconds
    digitalWrite(ledPins[i], LOW); // Turn the specified LED off
    delay(500); // Wait for 500 milliseconds
  }

}
