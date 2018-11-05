//==============================================================================
// This is what will happen evertime the timer interrupt executes

void timerCallback()
{
  if (airqualitysensor.counter == 122)//set 2 seconds as a detected duty
  {
    airqualitysensor.last_vol = airqualitysensor.first_vol;
    airqualitysensor.first_vol = analogRead(A0);
    airqualitysensor.counter = 0;
    airqualitysensor.timer_index = 1;
    
    if (digitalRead(LED_BUILTIN) == HIGH)
    {
      digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    
  }
  else
  {
    airqualitysensor.counter++;
  }
}

//==============================================================================
