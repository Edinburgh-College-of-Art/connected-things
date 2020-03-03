// This is a non-void function, which means it returns a value – in this case an it

int readJson(String jsonString)
{
  DynamicJsonDocument jsonBuffer(2048); // Create a new DynamicJsonDocument and allocate memory on the Arduino to hold it
  deserializeJson(jsonBuffer, jsonString); // Copy the data in the String from Adafruit IO into a new JsonObject
  JsonObject json = jsonBuffer.as<JsonObject>();

  int number = json["number"]; // Extract the values you want from the received JSON
  String atTime = json["time"];

  Serial.println("Number: " + String(number) + ", received at: " + atTime); // Print the values you get to the Serial

  return number; // Return the number you extracted from the JSON
}
