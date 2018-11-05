//==============================================================================
// This is what will happen evertime the timer interrupt executes

void timerCallback()
{
  digitalWrite(ledPin, ledState);
  ledState = !ledState;
}

//==============================================================================
