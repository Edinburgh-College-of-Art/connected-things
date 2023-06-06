/* This sketch demonstrates a simple way to receive data from the Adafruit IO service and map the data to the
   movement of a Servo.
   NOTE: To use this example you will need to setup your own Adafruit IO account, and a feed to subscribe to
   You will also need to make sure you have the Adafruit_MQTT and Adafruit_MQTT_Client libraries installed

   THINGS YOU NEED TO CHANGE:
   Lines 20, 21 > Replace with the details for your local WiFi network
   Lines 27, 28 > Replace with your Adafruit IO username and API Key
   Line 42 > Replace with your Feed's MQTT Key
 */

// Libraries ---------------------------------------------
#include <WiFiNINA.h> // Use this WiFi Library for the Nano 33 IoT
// #include <WiFi101.h> // Use this WiFi Library for the Feather M0
#include <Adafruit_MQTT.h> // You will need these Adafruit Libraries to connect to Adafruit IO
#include <Adafruit_MQTT_Client.h>
#include <Servo.h> // Remember to import the Servo library

// WiFi --------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO -------------------------------------------
// These values will be the same for all your programs – so you can copy and paste them without changing anything
#define ioServer "io.adafruit.com" // define the address of the Adafruit IO Server
#define ioPort 1883 // define the port number for MQTT communication
#define ioUsername "your_adafruit_io_username" // define your Adafruit username
#define ioKey "your_adafruit_io_key" // define your Adafruit API Key

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
Adafruit_MQTT_Subscribe dataFeed = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Create a new Adafruit MQTT Subscribe object
// Pass in the MQTT client and ioUsername defined above, and the name of the feed you created on the Adafruit IO website

// Servo -------------------------------------------------
Servo servo; // Create a new Servo object and give it a name
const int servoPin = 7; // Create a new const int to hold the number of the pin your servo is attached to


// Setup -------------------------------------------------
void setup()
{
  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial)
  {} // Do nothing until the Serial port is open

  connectToWiFi(ssid, password); // Connect to the local WiFi network

  servo.attach(servoPin); // Tell the Arduino which pin the servo is attached to
  servo.write(0); // Move the servo to its starting position (0 degrees)

  mqtt.subscribe(&dataFeed); // Subscribe to the feed you set up above

} // End of setup
// Loop --------------------------------------------------
void loop()
{
  connectToMQTT(); // Connect to Adafruit IO using MQTT

  Adafruit_MQTT_Subscribe *subscription; // Create a new Adafruit MQTT Subscribe object

  /* The while() loop here is bascially telling the Arduino to wait for 2 seconds to read incoming data before moving
     on to the next task, checking which feed it is receiving data from (in this example we only have one, but we could
     have more, and doing something with it.

     An important point to note about Adafruit IO is that all the data is received as a char array. This means that to use
     the numbers you receive from Adafruit, you will need to do a bit of conversion. This example assumes the data you are
     receiving from Adafruit is a number between 0 and 1023 (e.g. the output from a sensor attached to another Arduino).
   */

  while ((subscription = mqtt.readSubscription(2000)))
  {
    if (subscription == &dataFeed)  // If the alert is from the feed defined above
    {
      Serial.print("Got: ");
      Serial.println((char *)dataFeed.lastread); // Print the received value to the Serial monitor

      String ioData = (char*)dataFeed.lastread; // Convert the received char array to a String

      int servoPos = ioData.toInt(); // Create a new int to hold the received data, and convert the ioData String to an int
      Serial.print("servoPos: "); // Print the result to the Serial
      Serial.println(servoPos);

      servoPos = map(servoPos, 0, 1023, 0, 180); // Map the value you received to the possible range of servo positions
      Serial.print("Updated servoPos: "); // Print the updated value of servoPos to the Serial
      Serial.println(servoPos);
      servo.write(servoPos); // move the servo to its new position
    } // End of if() statement
  } // End of while() loop

} // End of loop
