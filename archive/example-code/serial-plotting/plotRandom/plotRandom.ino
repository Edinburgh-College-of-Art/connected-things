/*
 * Plot multiple random graphs in serial plotter at the fastest possible rate
 * 
 */
//====================================================================================
const unsigned long baud = 9600;
unsigned int bytesPerSec = baud / 10;
unsigned int numberSize = sizeof(int); // how many bytes is a number
unsigned int minMicroDelay = 1e6 / (bytesPerSec * numberSize); // the shortest we can wait before sending the next message
//====================================================================================
int graphNum = 2; // number of random signals
//====================================================================================

void setup()
{
  Serial.begin(baud);
  while (!Serial) {}  // Wait to open serial monitor before continuing
  randomSeed(analogRead(0));
}

//====================================================================================

void loop()
{
  for (int i = 0; i < graphNum; ++i)
  {
    //--------------------------------------------------------------------------------------------
    Serial.print(random(1024));
    delayMicroseconds(minMicroDelay); // we ideally need to wait this period of time before sending something else to serial

    Serial.print(","); // need a space, comma, semicolon something to delimit the numbers coming in
    delayMicroseconds(minMicroDelay);
  }
  //--------------------------------------------------------------------------------------------
  Serial.println(512); // centre line
  delayMicroseconds(minMicroDelay);
  //--------------------------------------------------------------------------------------------
}
