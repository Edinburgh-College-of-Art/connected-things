/* This sketch demonstrates a simple way to receive data from the Adafruit IO service
   NOTE: To use this example you will need to setup your own Adafruit IO account, and a feed to subscribe to
   You will also need to make sure you have the Adafruit_MQTT and Adafruit_MQTT_Client libraries installed

   THINGS YOU NEED TO CHANGE:
   Lines 18, 19 > Replace with the details for your local WiFi network
   Lines 25, 26 > Replace with your Adafruit IO username and API Key
   Line 40 > Replace with your Feed's MQTT Key */


// Libraries ---------------------------------------------
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

// WiFi --------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO -------------------------------------------
// These values will be the same for all your programs – so you can copy and paste them without changing anything
#define ioServer "io.adafruit.com" // define the address of the Adafruit IO Server
#define ioPort 1883 // define the port number for MQTT communication
#define ioUsername "your_adafruit_io_username" // replace with your Adafruit IO username
#define ioKey "your_adafruit_io_api_key" // replace with your Adafuit IO API Key

// Clients -----------------------------------------------
WiFiClient client; // Create a new WiFi client
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey); // Create a new Adafruit MQTT Client and pass in the values defined above
// It is really imporant you pass the values in in the correct order – if you don't you will not be able to connect

/* Note the "&" in front of "client" both here and in the below "Adafruit_MQTT_Publish" declaration – this is a pointer. What it basically means it that
   what is returned by the variable "&client" is the memory address of the variable, as opposed to the value that is at that location. You do not need to
   understand the computer science behind this for what we are doing, just that we are using it here because it is what the Adafruit MQTT library is
   expecting. If you do want to know more about pointers, there is an Arduino Forum thread here which may help: https://forum.arduino.cc/index.php?topic=484402.0
 */

// Feed --------------------------------------------------
Adafruit_MQTT_Subscribe widgetAlert = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Create a new Adafruit MQTT Subscribe object
// Pass in the MQTT client and ioUsername defined above, and the name of the feed you created on the Adafruit IO website

// LED ---------------------------------------------------
const int ledPin = 9; // Create an int to hold the number of the pin your LED is connected to

// Timer -------------------------------------------------
const long timer = 5000; // Create a long to hold the time (in milliseconds) you want the LED to remain on after receiving data
long pTime = 0; // Create a long to keep track of the last time you turned the led on and off


// Setup -------------------------------------------------
void setup()
{
  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // Do nothing until the Serial port is open

  connectToWiFi(ssid, password); // Connect to the local WiFi network

  pinMode(ledPin, OUTPUT); // Set the pinMode for your LED pin

  mqtt.subscribe(&widgetAlert); // Subscribe to the feed you set up above

} // End of setup
// Loop --------------------------------------------------
void loop()
{
  connectToMQTT(); // Connect to Adafruit IO using MQTT

  Adafruit_MQTT_Subscribe *subscription; // Create a new Adafruit MQTT Subscribe object

  /* The while() loop here is bascially telling the Arduino to wait for 5 seconds to read incoming data before moving
     on to the next task, checking which feed it is receiving data from (in this example we only have one, but we could
     have more, and doing something with it.
   */

  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &widgetAlert)  // If the alert is from the feed defined above
    {
      Serial.print("Got: ");
      Serial.println((char *)widgetAlert.lastread); // Print the received value to the Serial monitor
      digitalWrite(ledPin, HIGH); // Turn the LED on
      pTime = millis(); // Update the value of pTime to match the current time
    }
  }

  if (millis() > pTime + timer)  // If five seconds have elapsed since the last time the timer was triggered
  {
    pTime = millis(); // Update the value of pTime to match the current time
    if (digitalRead(ledPin) == HIGH)  // If the LED is on...
    {
      digitalWrite(ledPin, LOW); // ... turn it off.
    }
  }

} // End of loop
