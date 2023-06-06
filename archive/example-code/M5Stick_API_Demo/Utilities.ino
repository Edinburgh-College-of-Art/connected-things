void halt() {
  while (1) {
    delay(1000);
    yield();
  }
}



void reset() {
  do {
    delay(20);
  } while (M5.Axp.GetBtnPress());
  M5.Beep.mute();
  ESP.restart();
}