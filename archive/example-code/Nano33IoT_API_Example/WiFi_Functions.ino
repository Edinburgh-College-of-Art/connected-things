void connectToWiFi() {  
  static const unsigned int timeout = 20000;
  WiFi.begin(ssid, pass);
  unsigned long startConnection = millis();

  while (WiFi.status() != WL_CONNECTED) {    
    if (millis() - startConnection > timeout) {
      Serial.println("Failed to connect\nPress reset");
      halt();
    }
  }

  Serial.println("Connected to:\n  ");
  Serial.println(ssid);
}

//---------------------------------------------------------------------------------------------------------------------------------------
void httpRequest(const String host, const String url) {
  if (client.connect(host.c_str(), 80)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("connection failed");
  }
  client.println("GET  " + url + " HTTP/1.1");
  client.println("Content-Type: text/json;charset=UTF-8");
  client.println("Host: " + host);
  client.println("Connection: disconnect");
  client.println();
}
//---------------------------------------------------------------------------------------------------------------------------------------
String asyncHttpResponse() {
  while (client.available()) {
    String response = client.readStringUntil('\r');
    Serial.print(response.c_str());
    int bodyIndex = response.indexOf("[{");
    if (bodyIndex >= 0) {
      return response.substring(bodyIndex);
    }
  }
  return "";
}
//---------------------------------------------------------------------------------------------------------------------------------------
String waitForHttpResponse() {

  const unsigned long timeout = 10000;
  const unsigned long startTimer = millis();
  while (client.available() == 0 or (millis() - startTimer) > timeout) {
    delay(100);    
  }
  bool bodyStarts = false;

  // Serial.println("RESPONSE");
  // Header
  while (client.available()) {
    String response = client.readStringUntil('\n');
    if (response.length() == 1) break;
  }
  // Body
  String responseData = "";
  bool isData = false;
  while (client.available()) {

    if (isData)
      responseData += client.readStringUntil('\n');
    else
      client.readStringUntil('\n');
    
    isData = !isData;
  }
  Serial.println("GotResponse");

  return responseData;
}