void gameOver()
{
  Serial.println("Game Over!");
  while (true) {
    sos();
  }
}
//==============================================================================
void waitForSerial()
{
  while (!Serial) {}
}
//==============================================================================
void waitForSerialInput()
{
  Serial.println("\n\nSend a character to run the mem dumper again!");
  Serial.flush();
  while (!Serial.available()) {}
  ;
  while (Serial.available()) {
    Serial.read();
  }
  Serial.flush();
  Serial.println("Waiting for another ISO14443A Card");
}
//==============================================================================
void sos()
{
  const int dot = 200, dash = 800;
  for (int i = 0; i < 3; ++i)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dot);
    digitalWrite(LED_BUILTIN, LOW);
    delay(dot);
  }
  for (int i = 0; i < 3; ++i)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dash);
    digitalWrite(LED_BUILTIN, LOW);
    delay(dash);
  }
  for (int i = 0; i < 3; ++i)
  {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(dot);
    digitalWrite(LED_BUILTIN, LOW);
    delay(dot);
  }
  delay(dash);
}
//==============================================================================
void beep()
{
  pinMode(buzzerPin, OUTPUT);
  tone(buzzerPin, 3000, 100);
}
