// The code on this tab is a general template for downloading data in JSON format from an API

// The values you pass into this function are the host name of the API you want to talk to, 
// the url request string, and the port number you want to use (80 or 443)

String getJson(String host, String url, const int port) { // This is a non-void function, which means that it returns a value (a String in this case)

  String payload; // create a String to hold the data you get back from the server 

  if (client.connect(host.c_str(), port)) { // connect to the server
    Serial.println("Connected to server."); // print a message to the Serial port to let you know the connection is successful

    client.println("GET " + url + " HTTP/1.1"); // send your GET request to the server
    client.println("Host: " + host);
    client.println("Connection: close"); // close the connection to teh server
    client.println(); // remember to print a line break at the end – this is to let the server know you've finished sending your request
  }

  while (client.connected()) { // while you are connected to the server
    String line = client.readStringUntil('\n'); // read in the data it is sending you until you hit a line break
    if (line == "\r") {
      break;
    }
  }

  payload = client.readString(); // this line copies the JSON data from the server into the String you created above

  return payload; // return the string containing your JSON data

}
