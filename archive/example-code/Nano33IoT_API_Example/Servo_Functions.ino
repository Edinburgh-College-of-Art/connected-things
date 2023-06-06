void setupServo() {
  servo.attach(servoPin);
  
}

void setServoToPosition(int pos) {
   servo.write(pos);
}