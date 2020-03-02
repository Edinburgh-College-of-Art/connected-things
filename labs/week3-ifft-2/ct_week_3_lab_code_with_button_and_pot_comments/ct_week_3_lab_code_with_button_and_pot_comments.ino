// This sketch demonstrates how to send values to a Google Sheets spreadsheet using IFTTT when you press a button
// Remember you will need to set up you own IFTTT applet on the website and connect your Google account

// The first thing you need to do is import the WiFi library for your Arduino
// For the Feather M0 you need WiFi101
// For the Arduino Nano IoT 33 in your kit you need WiFiNINA - add this by going to Tools > Manage Libraries

// Libraries ---------------------------
#include <WiFi101.h> // for the Feather M0
// #include <WiFiNINA.h> // for the Nano IoT 33

// WiFi Network ------------------------
const char* ssid = "HANABI"; // If you are not at ECA, replace this with your local WiFi network name and password
const char* password = "lowernorwood";

// IFTTT -------------------------------
WiFiClient client; // Create a new WiFiClient – this is an unsecured connection (Port 80)

// Button and Potentiometer ------------
// I'm using a potentiometer as an input in this example – but the basic code will also work for other kinds of inputs/sensors

int button = 9; // create an int to hold the pin number that the push button is connected to
int pot = A7; // create an int to hold the pin number that the potentiometer is connected to - the A indicates this in an analog pin
// A potentiometer is a kind of variable resistor that gives different readings when you turn it
bool dataSent = false; // this boolean is used to stop the Arduino constantly sending requests to IFTTT when you press the button


// Setup -------------------------------
void setup() { // runs once

  // Call the function that connects you to the WiFi network (on WiFi_Utils tab), passing in the values for ssid and password
  connectToWiFi(ssid, password);

  pinMode(button, INPUT); // tell the Arduino that the button connected to pin 9 is an input
  pinMode(pot, INPUT); // tell the Arduino the potentiometer connected to pin A7 is an input
}

// Loop ---------------------------------
void loop() { // runs continuously

  int potReading = analogRead(pot); // read the value of the potentiometer on pin A7
  int v2 = int(random(1024)); // I'm generating random numbers for value 2 and 3 again – but you could equally replace these with other sensors
  int v3 = int(random(1024));

  // In this example if the button is not pressed it reads LOW (0), if it is pressed it reads HIGH (1)
  if (digitalRead(button) == LOW) { // check if the button is pressed – if it is
    dataSent = false; // set dataSent to false and do nothing else
  } else { // if it is pressed (i.e. reads HIGH)
    // this next if statement is to stop the Arduino sending GET requests to IFTTT the whole time the button is pressed - without it you will very quickly exceed your rate limit!
    if (!dataSent) { // check if dataSent is false
      dataSent = true; // set dataSent to true (to stop the connectToIFTTT function being called more than once for each button press) 
      Serial.println("Sending data..."); // print a message to the Serial port to let you know the button has been pressed
      connectToIFTTT(potReading, v2, v3); // call the connectToIFTTT function (on the IFTTT tab), passing in the reading of the potentiometer and two random numbers that you generated above
    }
  }

}
