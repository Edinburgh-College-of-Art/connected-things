/* This sketch demonstrates how to receive and parse JSON Data from Adafruit IO, and use it to change the position of a servo.
   NOTE: For this sketch to work, you will need to either set up an IFTTT Note Widget, or another Arduino to send JSON data to
   send JSON Data to Adafruit IO. See the Week 7 Slides, and 'Adafruit IO JSON Publish' example code on Learn for examples of how
   to do this.

   THINGS YOU NEED TO CHANGE:
   Lines 22, 23 > Replace with the details for your local WiFi network
   Lines 29, 30 > Replace with your Adafruit Username and API Key
   Line 44 > Replace with your Feed's MQTT Key

 */

// Libraries ------------------------------------------------------------------
#include <WiFiNINA.h> // Use this WiFi Library for the Nano 33 IoT
// #include <WiFi101.h> // Use this WiFi Library for the Feather M0
#include <Adafruit_MQTT.h> // You will need these Adafruit Libraries to connect to Adafruit IO
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h> // Import the Arduino JSON Library
#include <Servo.h> // Import the Servo Library

// WiFi -----------------------------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO ----------------------------------------------------------------
// These values will be the same for all your programs – so you can copy and paste them without changing anything
#define ioServer "io.adafruit.com" // Define the address of the Adafruit IO Server
#define ioPort 1883 // Define the Port Number for MQTT communication
#define ioUsername "your_adafruit_username" // Define your Adafruit Username
#define ioKey "your_adafruit_api_key" // Define your Adafruit API Key

// Clients -------------------------------------------------------------------
WiFiClient client; // Create a new WiFi client
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey); // Create a new Adafruit MQTT Client and pass in the values defined above
// It is really important you pass these values in in the correct order – if you don't you will not be able to connect

/* Note the "&" in front of "client" both here and in the below "Adafruit_MQTT_Subscribe" declaration – this is a pointer. What it basically means it that
   what is returned by the variable "&client" is the memory address of the variable, as opposed to the value that is at that location. You do not need to
   understand the computer science behind this for what we are doing, just that we are using it here because it is what the Adafruit MQTT library is
   expecting. If you do want to know more about pointers, there is an Arduino Forum thread here which may help: https://forum.arduino.cc/index.php?topic=484402.0
 */

// Feed ----------------------------------------------------------------------
Adafruit_MQTT_Subscribe widgetAlert = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Create a new Adafruit MQTT Subscribe object
// Pass in the MQTT client and ioUsername defined above, and the key for the feed you created on the Adafruit IO website

// Servo ---------------------------------------------------------------------
Servo servo; // Create a new Servo object and give it a name
const int servoPin = 7; // Create a new const in to hold the number of the pin your servo is attached to


// Setup ---------------------------------------------------------------------
void setup()
{
  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // Do nothing until the Serial port is open

  connectToWiFi(ssid, password); // Connect to the local WiFi network

  servo.attach(servoPin); // Tell the Arduino which pin the servo is attached to
  servo.write(0); // Move the servo to its starting position

  mqtt.subscribe(&widgetAlert); // Subscribe to the feed you set up above

} // End of setup
// Loop ---------------------------------------------------------------------
void loop()
{
  connectToMQTT(); // Connect to Adafruit IO using MQTT

  Adafruit_MQTT_Subscribe *subscription; // Create a new Adafruit MQTT Subscribe object

  /* The while() loop here is bascially telling the Arduino to wait for 2 seconds to read incoming data before moving
     on to the next task, checking which feed it is receiving data from (in this example we only have one, but we could
     have more, and doing something with it.

     An important point to note about Adafruit IO is that all the data is received as a char array. This means that to use
     the numbers you receive from Adafruit, you will need to do a bit of conversion. This example assumes you are publishing
     JSON data to your feed in the following format: {"number":XXX,"time":"XXXXX"}, where number is an int and time a String
   */

  while ((subscription = mqtt.readSubscription(2000)))
  {
    if (subscription == &widgetAlert)  // If the incoming data is from the feed defined above
    {
      String lastRead = (char*)widgetAlert.lastread; // Copy the received data into a String

      Serial.print("Got: "); // Print the received data to the Serial
      Serial.println(lastRead);

      int recVal = readJson(lastRead); // Create a new int and use the readJson() function (on JSON_Utils tab) to extract the int value from received JSON
      int servoPos = map(recVal, 0, 1023, 0, 180); // Create a new int and the received value to a number between 0 and 180
      servo.write(servoPos); // Update the position of the servo
    }
  }

}
