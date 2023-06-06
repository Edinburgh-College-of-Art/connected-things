//==============================================================================

int getAirQuality() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= 200) {
    //--------------------------------------------------------------------------
    previousMillis = currentMillis;
    //--------------------------------------------------------------------------
    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = analogRead(A0);

    digitalWrite(LED_BUILTIN, !(digitalRead(LED_BUILTIN) == HIGH));  // alternate the LED: kind of hacky, try not to do this
    analyseAirQuality(airqualitysensor.slope());
    //--------------------------------------------------------------------------
  }
}

//==============================================================================
// With the last reading of the air quality, do something

void analyseAirQuality(uint8_t current_quality) {
  Serial.print("Air Quality Reading: ");
  Serial.println(airqualitysensor.first_vol);
  switch (current_quality) {
    case (0):
      {
        Serial.println("High pollution! Do Something About It!");
        break;
      }
    case (1):
      {
        Serial.println("High pollution!");
        break;
      }
    case (2):
      {
        Serial.println("Low pollution!");
        break;
      }
    case (3):
      {
        Serial.println("Fresh air");
        break;
      }
  }
}