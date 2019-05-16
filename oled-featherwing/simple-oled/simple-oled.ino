/*
   Simple OLED Example for Adafruit 128x32 monochrome OLED display
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//------------------------------------------------------------------------
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);
//------------------------------------------------------------------------
// OLED FeatherWing buttons map to different pins depending on board:
#if defined(ESP8266)
#define BUTTON_A  0
#define BUTTON_B 16
#define BUTTON_C  2
#else // 32u4, M0, M4, nrf52840 and 328p
#define BUTTON_A  9
#define BUTTON_B  6
#define BUTTON_C  5
#endif
//------------------------------------------------------------------------
void setup()
{
  //----------------------------------------------------------------------
  Serial.begin(9600);
  //----------------------------------------------------------------------
  pinMode(BUTTON_A, INPUT_PULLUP);
  pinMode(BUTTON_B, INPUT_PULLUP);
  pinMode(BUTTON_C, INPUT_PULLUP);
  //----------------------------------------------------------------------
  setupOLED();
  delay(1000);
  //----------------------------------------------------------------------
  clearScreen();
  Serial.println("IO test");
  showTestDisplay();
  //----------------------------------------------------------------------
}
//------------------------------------------------------------------------
void loop()
{
  if (!digitalRead(BUTTON_A))
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("A");
  }
  if (!digitalRead(BUTTON_B))
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("B");
  }
  if (!digitalRead(BUTTON_C))
  {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.print("C");
  }
  delay(10);
  // Single core design has a real time component that is 
  // not documented but required cycle time, so Arduino code needs 
  // to constantly yield() or the RTOS component will reset/crash
  yield(); 
  display.display();
}
//------------------------------------------------------------------------
