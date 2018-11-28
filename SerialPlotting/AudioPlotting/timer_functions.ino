//SET UP TIMER 1
void InitTimer()
{
  cli();        //Disable global interrupts
  TCCR1A = 0;   //Reset Timer 1 Counter Control Register A
  TCCR1B = 0;   //Reset Timer 1 Counter Control Register B
  //Set Timer 1 Output Compare Register A to desired frequency
  OCR1A = floor(16 * (pow(10, 6)) / sampleRate) - 1; // = (16*10^6) / (samplingRate) - 1 (must be <65536)

  TCCR1B |= (1 << WGM12); // turn on CTC mode (clear timer on compare match)
  TCCR1B |= (1 << CS10);   // Set CS10 and CS12 bits for 1024 prescaler
  TIMSK1 |= (1 << OCIE1A); // enable timer interrupt

  sei(); //enable interrupts
}
