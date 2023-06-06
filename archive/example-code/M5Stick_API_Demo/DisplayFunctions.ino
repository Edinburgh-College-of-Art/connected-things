void setupDisplay() {
  M5.Lcd.setRotation(1);
  M5.Lcd.setTextSize(1);
  M5.Lcd.setTextColor(WHITE);
}


void LCD_Clear() {
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.setTextColor(WHITE);
  M5.Lcd.setTextSize(2);
}

void animateEllipses(int16_t& x, int16_t& y) {
  static byte i = 0;

  if (i > 2) {
    i = 0;
    M5.Lcd.setCursor(x, y);
    M5.Lcd.setTextColor(BLACK);
    M5.Lcd.printf(".....");
    M5.Lcd.setTextColor(WHITE);
    M5.Lcd.setCursor(x, y);
  }
  M5.Lcd.printf(".");
  i++;
}