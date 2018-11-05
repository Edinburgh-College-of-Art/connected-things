/*  Connects to the home WiFi network
 *  Asks some network parameters
 *  Starts WiFi server with fix IP and listens
 *  Receives and sends messages to the client
 *  Communicates: wifi_client_01.ino
 */
 //==============================================================================
#include <SPI.h>
#include <WiFi101.h>
//==============================================================================
byte ledPin = 13;
char ssid[] = "FeatherServer"; // SSID of your home WiFi
char pass[] = "1234567890";    // AP password (needed only for WEP, must be exactly 10 or 26 characters in length) and HEX
int keyindex = M2M_WIFI_SEC_WEP;
//==============================================================================
WiFiServer server(80);
int status = WL_IDLE_STATUS;                    
IPAddress ip(192, 168, 0, 80);            // IP address of the server
IPAddress gateway(192,168,0,1);           // gateway of your network
IPAddress subnet(255,255,255,0);          // subnet mask of your network
//==============================================================================
void setup() 
{
  setAccessPoint(ssid, keyindex, pass, ip); 
  pinMode(ledPin, OUTPUT);
}

//==============================================================================

void loop () 
{
  WiFiClient client = server.available();
  if (client) 
  {
    if (client.connected())
    {
      digitalWrite(ledPin, LOW);  // to show the communication only (inverted logic)
      Serial.println(".");
      String request = client.readStringUntil('\r');    // receives the message from the client
      Serial.print("From client: "); Serial.println(request);
      client.flush();
      client.println("Hi client! No, I am listening.\r"); // sends the answer to the client
      digitalWrite(ledPin, HIGH);
    }
    client.stop();                // tarminates the connection with the client
  }
}

//==============================================================================

void errorProtocol()
{
  while (true)
  {
    // do something if there is a problem
  }
}
