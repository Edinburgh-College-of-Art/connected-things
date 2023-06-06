/* This sketch provides a basic template for connecting Adafruit IO via MQTT, publishing data from
   your Arduino, and scubscribing to a feed from Adafruit. */

// Libraries ----------------------------------------------------------------------------------
#include <WiFiNINA.h> // Use this WiFi Library for the Nano 33 IoT
//#incldue <WiFi101.h> // Use this WiFi Library for the Feather M0
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// WiFi ---------------------------------------------------------------------------------------
const char* ssid = "your_ssid"; // Replace with the ssid for your local WiFi network
const char* password = "your_password"; // Replace with the password for your local WiFi network

// Adafruit IO --------------------------------------------------------------------------------
#define ioServer "io.adafruit.com"
#define ioPort 1883
#define ioUsername "your_adafruit_username" // Define your Adafruit Username
#define ioKey "your_adafruit_api_key" // Define your Adafruit API Key

// Clients ------------------------------------------------------------------------------------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey);

// Feeds --------------------------------------------------------------------------------------
Adafruit_MQTT_Publish publishFeed = Adafruit_MQTT_Publish(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key"); // Replace with the MQTT Keys for your Feeds
Adafruit_MQTT_Subscribe subscribeFeed = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/your_feeds_mqtt_key");

// Publish Timer -----------------------------------------------------------------------------
const long timer = 5000;
long pTime;

// Setup -------------------------------------------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {}

  connectToWiFi(ssid, password);

  mqtt.subscribe(&subscribeFeed);

} // End of setup
// Loop --------------------------------------------------------------------------------------
void loop()
{
  connectToMQTT();

  Adafruit_MQTT_Subscribe *subscription;

  while ((subscription = mqtt.readSubscription(2000)))
  {
    if (subscription == &subscribeFeed)
    {
      Serial.print("Data received: ");
      Serial.println((char*)subscribeFeed.lastRead);

      // Do something with the data you've received...
    }
  }

  if (millis() > pTime + timer)
  {
    // Create some data to send to Adafruit IO...

    if (!publishFeed.publish(/*YOUR_DATA*/))
    {
      Serial.println("Failed!");
    }
    else
    {
      Serial.println("OK!");
    }
  }

} // End of Loop
