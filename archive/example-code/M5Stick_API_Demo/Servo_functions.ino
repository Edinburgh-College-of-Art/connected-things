#define COUNT_LOW 1500
#define COUNT_HIGH 8500
#define TIMER_WIDTH 16

void setupServo() {
  const int servoPin = 26;
  ledcSetup(1, 50, TIMER_WIDTH);
  ledcAttachPin(26, 1);
}

void setServoToPosition(int pos) {
  ledcWrite(1, map(pos, 0, 180, COUNT_LOW, COUNT_HIGH));
}