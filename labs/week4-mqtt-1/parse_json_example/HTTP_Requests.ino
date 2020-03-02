// The code on this tab is a general template for downloading data in JSON format from an API

// The values you pass into this function are the host name of the API you want to talk to (e.g. api.darksky.net, maker.ifttt.com)
// and the url request string
String getJson(String host, String url) { // This is a non-void function, which means that it returns a value, in this case a String
  
  String response; // create a new String to hold the data you get back from the Server

  if (client.connect(host.c_str(), 443)) { // connect to the server using port 443 (secure connection)
    Serial.println("Connected to server."); // print a message to the Serial port to let you know you've connected successfully
    client.println("GET " + url + " HTTP/1.1"); // sent your GET request to the server
    client.println("Host: " + host);
    client.println("Connection: close"); // close the connection to the server
    client.println(); // remember to print a line break at the end – this is to let the server know you've finished sending your request
  }

  while (client.connected()) { // while you are connected to the server 
    String line = client.readStringUntil('\n'); // read in the data it is sending you until you hit a line break
    if (line == "\r") {
      break;
    }
    Serial.println(line); // print out the data you've got back to the Serial port to check the response is OK (Response Code 200)
  }

  response = client.readString(); // this line copies the JSON data from the server into the String you created above 
  Serial.println(response); // print out the JSON data you've got to the Serial port

  return response; // return the String called response

}
