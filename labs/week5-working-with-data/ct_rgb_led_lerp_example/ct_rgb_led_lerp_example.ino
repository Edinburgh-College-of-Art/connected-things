// This sketch demonstrates the use of a while() loop and gradually changing the colour of an RGB LED using linear interpolation
// Linear interpolation is a way of calculating intermediate values between a start value and an end value
// It is useful for achieveing smooth transitions from one state to another (e.g. from one colour to another)
// For a further explanation of linear interpolation see: https://www.youtube.com/watch?v=ZyYq91cAk1o
// For more information on RGB LEDs: https://create.arduino.cc/projecthub/muhammad-aqib/arduino-rgb-led-tutorial-fc003e

// First, variables to hold the pin number for each of the RGB LED's colour elements (red, green, blue)
const int redLed = 5;
const int greenLed = 2;
const int blueLed = 3;

// Next, create some variables to hold the red, green, and blue values for your LED – this will always hold the current value
float red = 0;
float green = 0;
float blue = 0;

const long timer = 10000; // Create a long to use as a timer – in this example the timer is set to 10 seconds
long pTime; // Create a long to keep track of the elapsed time

// Setup -------------------------------------------------------
void setup() {

  // Set the pinMode for each of your LED's elements
  pinMode(redLed, OUTPUT);
  pinMode(greenLed, OUTPUT);
  pinMode(blueLed, OUTPUT);

  // Use the updateLEDcolour function to set the initial colour of your LED
  // The values you pass in here are the length of transition you want (in milliseconds),
  // the current red, green, and blue values for your LED; and the red, green, and blue values of the colour you want to change to
  updateLEDcolour(2000, red, green, blue, 255, 255, 255);

}


// Loop --------------------------------------------------------
void loop() {

  // millis() always returns the time in milliseconds that has elapsed since the Arduino started running 
  if (millis() > pTime + timer) { // If ten seconds has elapsed since the timer was last triggered
    pTime = millis(); // Set pTime to millis()
    float r = random(0, 255); // Choose some random colour values for the LED to change to
    float g = random(0, 255);
    float b = random(0, 255); 
    updateLEDcolour(2000, red, green, blue, r, g, b); // Update the colour of the LED by calling the updateLEDcolour function (see below)
  }

}


// updateLEDcolour --------------------------------------------
void updateLEDcolour(long t, float sR, float sG, float sB, float eR, float eG, float eB) {
  // Remember the values you pass in here are the time (t) of the transition you want (i.e. how long the LED takes to change colour),
  // the starting colour values for your LED (sR, sG, sB), and the colour values you want the LED to change to (eR, eG, eB) 

// In this example we are interpolating the colours over time 
  long sTime = millis(); // sTime holds the time the transition started – so set it to equal millis()
  long lTime = millis() - sTime; // lTime will hold the time of each completed while() loop 

// A while() loop is a loop that will continue to execute as long as the condition in the brackets remains true
// For more information on while() loops see: https://www.arduino.cc/reference/en/language/structure/control-structure/while/

  while (lTime < t) { // The loop will continue to execute as long as the value of lTime is less than that of t
    float pos = (float)lTime / float(t); // Calculate how close you are to finishing the loop – this will return a value between 0.0 and 1.0
    red = lerp(sR, eR, pos, 0.0, 1.0); // Calculate new values for each of the colour elements in your LED using the lerp() fucntion (see below)
    green = lerp(sG, eG, pos, 0.0, 1.0);
    blue = lerp(sB, eB, pos, 0.0, 1.0);
    writeLEDcolour(red, green, blue); // Write the newly calculated colour values to the LED, using the writeLEDcolour function (see below)
    lTime = millis() - sTime; // update the value of lTime 
  }

  Serial.println("Done lerping!"); // Print a message to the Serial – to let you know the loop is finished

}


// Lerp --------------------------------------------------------
float lerp(float sCol, float eCol, float t, float sTime, float eTime) {
  // The values you are passing in here are the starting value for each individual colour channel (sCol). 
  // the value you want to change to (eCol), your current position in the while() loop (t),
  // and the minimum and maximum values calculated by pos in your while() loop - these will always be 0.0 (min) and 1.0 (max)

  // The next line uses the mathematical formula for linear interpolation to calculate a new value for your LED's colour channel
  // You can re-use this equation for values other than colour, so you do not need to fully understand the mathematics behind it; 
  // however you do need to understand how to pass variables to it to calculate intermediate values for your project 

  float nCol = sCol + (eCol - sCol) * ((t - sTime) / (eTime - sTime));
  return nCol; // Return the newly calculated value for nCol

}


// writeLEDcolour ----------------------------------------------
void writeLEDcolour(float r, float g, float b) {

  // The Arduino's analogWrite() function expects ints, so the floats we pass in here need to be converted
  // This is what that code int(r), int(g), and int(b) in the brackets is doing 

  analogWrite(redLed, int(r));
  analogWrite(greenLed, int(g));
  analogWrite(blueLed, int(b));

}
