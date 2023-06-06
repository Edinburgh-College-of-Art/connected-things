/* This sketch demonstrates how to publish a sensor reading to the Adafruit IO Service
   NOTE: To use this example sketch you will need to setup your own Adafruit IO account, and feed to publish to
   You will also need to make sure you have the Adafruit_MQTT and Adafruit_MQTT_Client libraries installed

   THINGS YOU NEED TO CHANGE:
   Lines 17, 18 > Replace with details for your local WiFi network
   Lines 24, 25 > Replace with your own Adafruit IO username and API key
   Line 39 > Replace with your Feed's MQTT key */

// Libraries -----------------------------------
#ifdef ARDUINO_SAMD_ZERO
#pragma message "You are Using the Feather M0"
#include <WiFi101.h>
#endif

#ifdef ARDUINO_SAMD_NANO_33_IOT
#pragma message "You are Using the IoT Nano 33"
#include <WiFiNINA.h>

#endif
#include < Adafruit_MQTT.h > // You will need these Adafruit Libraries to connect to Adafruit IO
#include <Adafruit_MQTT_Client.h>

// WiFi ----------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO --------------------------------
// These values will be the same for all your programs – so you can copy and paste them without changing anything
#define ioServer "io.adafruit.com" // define the address of the Adafruit IO Server
#define ioPort 1883 // define the port number for MQTT communication
#define ioUsername "your_adafruit_io_username" // replace with your Adafruit IO username
#define ioKey "your_adafruit_io_api_key" // replace with your Adafruit IO API Key

// Clients ------------------------------------
WiFiClient client; // Create a new WiFi client
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey); // Create a new Adafruit MQTT Client and pass in the values defined above
// It is really important you pass the values in in the correct order - if you don't you will not be able to connect

/* Note the "&" in front of "client" both here and in the below "Adafruit_MQTT_Publish" declaration – this is a pointer. What it basically means it that
   what is returned by the variable "&client" is the memory address of the variable, as opposed to the value that is at that location. You do not need to
   understand the computer science behind this for what we are doing, just that we are using it here because it is what the Adafruit MQTT library is
   expecting. If you do want to know more about pointers, there is an Arduino Forum thread here which may help: https://forum.arduino.cc/index.php?topic=484402.0
 */

// Feed ---------------------------------------
Adafruit_MQTT_Publish potFeed = Adafruit_MQTT_Publish(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Create a new Adafruit MQTT Publish object
// Pass in the MQTT client and ioUsername defined above, and the name of the feed you created on the Adafruit IO website

// Pot ---------------------------------------
const int potPin = A1; // Create an int to hold the number of the pin the potentiometer is attached to

// Timer -------------------------------------
long timer = 5000; // Create a long to hold the time (in milliseconds) you want to elapse between publishing to the Adafruit IO Server
long pTime = 0; // Create a long to keep track of the last time you published data to the Adafruit IO Server


// Setup -------------------------------------
void setup()
{
  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // Do nothing until the Serial port is open

  connectToWiFi(ssid, password); // connect to the local WiFi network

  pinMode(potPin, INPUT); // set the pinMode for your potentiometer pin

} // End of Setup
// Loop --------------------------------------
void loop()
{
  connectToMQTT(); // Connect to Adafruit IO using MQTT – see the MQTT_Utils tab for code

  if (millis() > pTime + timer)  // If five seconds has elapsed since the last time we published data to Adafruit IO
  {
    pTime = millis(); // Set pTime to the current time

    /* In this next section of code – you will notice that "potRead" is not an "int", but a "uint32_t" variable type – this is an "unsigned integer" with a
       width of exactly 32 bytes. A normal "int" in Arduino does not have a fixed width; but a "uint32_t" does (you can also have uints that are 8 16, and 64 bytes wide).
       An "unsigned integer" is one without a plus (+) or minus (-) sign in front of it – so it is always assumed to be positive. Again, for what we are doing you do
       not need to understand the computer science behind this – just know that the reason we are using it here is that the Adafruit MQTT library is expecting us to
       give it a very particular datatype.*/

    uint32_t potRead = analogRead(potPin); // Create an int to hold the reading from the potentiometer
    Serial.print("Sending Potentiometer Reading: "); // Print the current reading to the Serial port so you can see what's going on
    Serial.println(potRead);

    // The important part of this next if statement is the "potFeed.publish(potRead)" – this is the code that actually publishes the data to Adafruit IO.
    // The remainder is for error checking.

    if (!potFeed.publish(potRead))  // If the attempt to publish has not been successful...
    {
      Serial.println("Failed."); // ... print an error message.
    }
    else
    {
      Serial.println("OK!"); // But if it has been successful, print a success message to the Serial.
    }
  }

} // End of Loop
