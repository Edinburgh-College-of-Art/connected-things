/*
 *  Plot multiple graphs in serial plotter at the fastest possible rate
 */

const unsigned long baud = 9600;
unsigned int bytesPerSec = baud / 10;
unsigned int numberSize = sizeof(int); // how many bytes is a number
unsigned int minMicroDelay = 1e6 / (bytesPerSec * numberSize); // the shortest we can wait before sending the next message

void setup()
{
  Serial.begin(baud);
  while (!Serial) {}  // Wait to open serial monitor before continuing
}

void loop()
{
  //--------------------------------------------------------------------------------------------
  Serial.print(1);
  delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

  Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
  Serial.println(2); // last data stream is always a println
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
}
