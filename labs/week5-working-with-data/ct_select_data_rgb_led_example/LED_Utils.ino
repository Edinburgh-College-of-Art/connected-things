void setLEDcolour(int r, int g, int b) {

  analogWrite(redLed, r);
  analogWrite(greenLed, g);
  analogWrite(blueLed, b);

}
