// Libraries --------------------------------------------
#include <WiFiNINA.h> // Use this WiFi Library for the Nano 33 IoT
// #include <WiFi101.h> // Use this WiFi Library for the Feather M0
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>
#include <Servo.h>

// WiFi --------------------------------------------------
const char* ssid = "YOUR_SSID"; // Replace with the ssid for your local WiFi network
const char* password = "YOUR_PASSWORD"; // Replace with the password for your local WiFi network

// Adafruit IO -------------------------------------------
// These values will be the same for all your programs – so you can copy and paste them without changing anything
#define ioServer "io.adafruit.com"
#define ioPort 1883
#define ioUsername "YOUR_ADAFRUIT_USERNAME" // define your Adafruit username
#define ioKey "YOUR_ADAFRUIT_AIO_KEY" // define your Adafruit API Key

// Clients -----------------------------------------------
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, ioServer, ioPort, ioUsername, ioKey);

// Feeds --------------------------------------------------
Adafruit_MQTT_Subscribe dataFeed = Adafruit_MQTT_Subscribe(&mqtt, ioUsername "/feeds/YOUR_FEEDS_MQTT_KEY"); // Replace with your Feed's MQTT Key

// LED ----------------------------------------------------
const int ledPin = 9;

// Timer --------------------------------------------------
const long timer = 5000;
long pTime = 0;

// Servo -------------------------------------------------
Servo servo;
const int servoPin = 7;


// Setup --------------------------------------------------
void setup()
{
  Serial.begin(9600);
  while (!Serial)
  {}

  connectToWiFi(ssid, password);

  pinMode(ledPin, OUTPUT);

  servo.attach(servoPin);
  servo.write(0);

  mqtt.subscribe(&dataFeed);

} // End of setup
// Loop ---------------------------------------------------
void loop()
{
  connectToMQTT();

  Adafruit_MQTT_Subscribe *subscription; // Create a new Adafruit MQTT Subscribe object

  while ((subscription = mqtt.readSubscription(5000)))
  {
    if (subscription == &dataFeed)
    {
      Serial.print("Got: ");
      Serial.println((char *)dataFeed.lastread);

      digitalWrite(ledPin, HIGH);
      pTime = millis();

      String ioData = (char *)dataFeed.lastread;
      int recVal = ioData.toInt();
      int servoPos = map(recVal, 0, 1023, 0, 180);
      Serial.print("Moving servo to postion ");
      Serial.println(servoPos);

      servo.write(servoPos);

    }
  }

  // Turn the LED on and off ------------------------------
  if (millis() > pTime + timer)
  {
    pTime = millis();
    if (digitalRead(ledPin) == HIGH)
    {
      digitalWrite(ledPin, LOW);
    }
  }

} // End of loop
