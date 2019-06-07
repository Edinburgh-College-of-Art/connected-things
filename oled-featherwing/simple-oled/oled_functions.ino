
void setupOLED()
{
  Serial.println("OLED FeatherWing test");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Address 0x3C for 128x32

  Serial.println("OLED begun");
  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  display.display();
}

//---------------------------------------------------------

void showTestDisplay()
{  
  display.setTextSize(1); 
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to SSID\n`adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0, 0);
  display.display(); // actually display all of the above
}
//---------------------------------------------------------
void showWifiDetails()
{  
  display.setTextSize(1); 
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.print("Connecting to SSID\n`adafruit':");
  display.print("connected!");
  display.println("IP: 10.0.1.23");
  display.println("Sending val #0");
  display.setCursor(0, 0);
  display.display(); // actually display all of the above
}

//---------------------------------------------------------

void clearScreen()
{
    // Clear the buffer.
  display.clearDisplay();
  display.display();
}
//---------------------------------------------------------
void clearLine(byte line)
{
  line *= 8;
  for (int i = 0; i < 128; ++i)
  {
    for (int j = 0; j < 7; ++j)
    {
      display.drawPixel(i, line + j, BLACK);
    }
  }
  display.display();
}
