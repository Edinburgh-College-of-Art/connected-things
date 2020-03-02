/*  This sketch demonstrates a simple way to publish JSON Data to Adafruit IO.
    NOTE: To use this example you will need to setup your own Adafruit IO account, and a feed to publish to.

    THINGS YOU NEED TO CHANGE:
    Lines 18, 19 > Replace with the details for your local WiFi network
    Lines 25, 26 > Replace with your Adafruit username and API Key
    Line 40 > Replace with your Feed's MQTT Key
*/

// Libraries ----------------------------------------------------------------------------------
#include <WiFiNINA.h> // Use this WiFi Library for the Nano 33 IoT
//#incldue <WiFi101.h> // Use this WiFi Library for the Feather M0
#include <Adafruit_MQTT.h> // Import the Adafruit MQTT Libraries
#include <Adafruit_MQTT_Client.h>
#include <ArduinoJson.h> // Improt the Arduino JSON Library

// WiFi ---------------------------------------------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO --------------------------------------------------------------------------------
// These values will be the same for all your programs – so you can copy and past them without changing anything
#define ioServer "io.adafruit.com" // Define the address of the Adafruit IO Server
#define ioPort 1883 // Define the Port Number for MQTT communication
#define ioUsername "your_adafruit_username" // Define your Adafruit Username
#define ioKey "your_adafruit_api_key" // Define your Adafruit API Key

// Clients ------------------------------------------------------------------------------------
WiFiClient client; // Create a new WiFi client
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey); // Create a new Adafruit MQTT Client and pass in the values defined above
// It is really important you pass these values in in the correct order – if you don't you will not be able to connect

/* Note the "&" in front of "client" both here and in the below "Adafruit_MQTT_Publish" declaration – this is a pointer. What it basically means it that
  what is returned by the variable "&client" is the memory address of the variable, as opposed to the value that is at that location. You do not need to
  understand the computer science behind this for what we are doing, just that we are using it here because it is what the Adafruit MQTT library is
  expecting. If you do want to know more about pointers, there is an Arduino Forum thread here which may help: https://forum.arduino.cc/index.php?topic=484402.0
*/

// Feed --------------------------------------------------------------------------------------
Adafruit_MQTT_Publish arduinoData = Adafruit_MQTT_Publish(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Create a new Adafruit MQTT Publish object
// Pass in the MQTT client and ioUsername defined above, and the key for the feed you created on the Adafruit IO website

// Potentiometer -----------------------------------------------------------------------------
const int potPin = A1; // Create a const int to hold the number of the pin your potentiometer is attached to

// Timer -------------------------------------------------------------------------------------
long timer = 5000; // Create a new long to hold the time you want to elapse between publishing data to Adafruit IO
long pTime = 0; // Create a new long to keep track of the last time you published data to Adafruit IO


// Setup -------------------------------------------------------------------------------------
void setup() {

  Serial.begin(9600); // Open the Serial port and set the baud rate (communication speed)
  while (!Serial) {} // Do nothing until the Serial port is ready

  connectToWiFi(ssid, password); // Connect to the local WiFi network

  pinMode(potPin, INPUT); // Set the pin mode for your potentiometer

} // End of setup


// Loop --------------------------------------------------------------------------------------
void loop() {

  connectToMQTT(); // Connect to Adafruit IO via MQTT

  if (millis() > pTime + timer) { // If 5 seconds has elapsed since the last time you published data to Adafruit IO
    pTime = millis(); // Update the value of pTime

    int potRead = analogRead(potPin); // Create a new int to hold the reading from the potentiometer pin
    Serial.print("Pot Read: "); // Print the reading to the serial
    Serial.println(potRead);

    /* The following code will create a JSON Object in the following format: {"pot":XXX,"random":XXX} where both "pot" and "random" are ints.
       IMPORTANT: If your JSON Object includes a value called "value" Adafruit IO will automatically parse it and save it to your feed, and ignore any other JSON you send it.
       For example, if you send a JSON Object like this {"value":256,"random":512}, the data saved to your feed will only be the number 256, but if you send it a JSON Object like this
       {"pot":256,"random":512} it will store the full JSON Object on your Feed
    */

    const size_t capacity = JSON_OBJECT_SIZE(2); // Calculate the memory required for your JSON Object – the number in the brackets is the number of values you want to publish
    DynamicJsonDocument jsonPub(capacity); // Create a Dynamic Json Document and use the value calculated for 'capacity' to allocate memory for it on the Arduino
    jsonPub["pot"] = potRead; // Add the potentiometer reading to your JSON Document
    jsonPub["random"] = int(random(1023)); // Add a random number to your JSON Document

    String jsonStr; // create a new String
    serializeJson(jsonPub, jsonStr); // convert the JSON object as a String
    Serial.print("JSON String: "); // Print the String you just created to the Serial so you can check it looks ok
    Serial.println(jsonStr);

    /* IMPORTANT: You cannot send a JSON Object to Adafruit IO without first converting it to a char array – this is because the "publish()" function in the Adafruit MQTT Library
       can only accept uint32_t or const char* (char array) values. The following code demonstrates how to do this.
    */

    char jsonChar[jsonStr.length() + 1]; // Create a new char array and set the length to be equal to the length of the String you created above to hold your JSON, plus 1
    jsonStr.toCharArray(jsonChar, jsonStr.length() + 1); // Copy your String into the char array you just created

    /* The values you need to pass into the function "toCharArray" are the char array you want to copy the characters from your String into, and the length of that array.
       For more info on how toCharArray() works, see: https://www.arduino.cc/reference/en/language/variables/data-types/string/functions/tochararray/
    */

    Serial.println("Sending JSON potentiometer reading..."); // Print a message to the Serial port so you can keep track of what's going on

    // Remember, this "if" statement is mostly for error checking – the code that actually publishes the data is "arduinoData.publish(jsonChar)"
    if (! arduinoData.publish(jsonChar)) { // Publish the "jsonChar" char array to Adafuit IO
      Serial.println("Failed!"); // If it doesn't publish, print an error message
    } else {
      Serial.println("OK!"); // If if does publish successfully, print a message to let us know
    }

  }
}
