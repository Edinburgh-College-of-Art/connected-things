// This example uses an unsecured connection on Port 80, but remember – it is best to use SSL (Port 443)
// where you can, but you may need to update the SSL Certificates on the Feather M0
// Instructions for updating SSL Certifcates are here: https://learn.adafruit.com/adafruit-feather-m0-wifi-atwinc1500/updating-ssl-certificates

void connectToIFTTT(int val1, int val2, int val3) { 

  String host = "maker.ifttt.com"; // Create a string to hold the host address
  String apiKey = "your_api_key"; // Replace this with your API key from IFTTT
  String trigger = "/trigger/your_trigger"; // Replace your_trigger with the event name of your Webhook

  // Build your query string - using the values passed into the function
  // Remember – this needs to be a String so if you will have to convert the ints you pass in to a String – this is what String(val1) is doing
  String query = "?value1=" + String(val1) + "&value2=" + String(val2) + "&value3=" + String(val3);

  // put all the strings together to build your HTTP request 
  String request = trigger + "/with/key/" + apiKey + query;

  Serial.println("http://" + host + request); // this line prints your full request url to the Serial port
  // I have included this to help you test your HTTP request – if you copy and paste this line from the Serial monitor into your web browser you can check if it is working correctly

  if (client.connect(host.c_str(), 80)) { // connect to the Client using Port 80 (Unsecured Connection)
    Serial.print("Connected to IFTTT."); // prints a message to the Serial to tell you the connection is successful
    client.println("GET " + request + " HTTP/1.1"); // send your GET request to IFTTT
    client.println("Host: " + host);
    client.println("Connection: close"); // close the connection
    client.println(); // remember to include a line break at the end
  }

}
