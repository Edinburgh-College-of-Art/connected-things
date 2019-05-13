/*  Connects to the home WiFi network
    Asks some network parameters
    Sends and receives message from the server in every 2 seconds
    Communicates: wifi_server_01.ino
*/
//==============================================================================
#include <SPI.h>
#include <WiFi101.h>
//==============================================================================
uint8_t ledPin = 13;
//==============================================================================
char ssid[] = "FeatherServer";
char pass[] = "1234567890";        
int keyindex = M2M_WIFI_SEC_WEP;
unsigned long askTimer = 500;
//==============================================================================
int status = WL_IDLE_STATUS;                    
IPAddress server(192, 168, 0, 80); 
WiFiClient client;
//==============================================================================
void setup() 
{
  connectToWifiNetwork(ssid, keyindex, pass);
  pinMode(ledPin, OUTPUT);
}

//==============================================================================

void loop () 
{
  client.connect(server, 80);   // Connection to the server
  digitalWrite(ledPin, LOW);    // to show the communication only (inverted logic)
  Serial.println(".");
  client.println("Hello server! Are you sleeping?\r");  // sends the message to the server
  String answer = client.readStringUntil('\r');   // receives the answer from the sever
  Serial.println("from server: " + answer);
  client.flush();
  digitalWrite(ledPin, HIGH);
  delay(askTimer);                  // client will trigger the communication after two seconds
}

//==============================================================================

void errorProtocol()
{
  while (true)
  {
    // do something if there is a problem
  }
}
