/*
   PN532 Test Memory Dump

    Pin Map
    -------

  | Nano | PN532           |
  | ---- | --------------- |
  | VIN  | 3.3v            |
  | 13   | SCK             |
  | 12   | MISO            |
  | 11   | MOSI / SDA / TX |
  | 10   | SSEL / SCL / RX |
  | GND  | GND             |

*/
//==============================================================================
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
//==============================================================================
const uint8_t buzzerPin = 6;
//==============================================================================
const uint8_t sselPin = 10;
const uint8_t numPlayers = 5;
uint32_t player[numPlayers] = {0};
uint8_t idIndex = 0;
Adafruit_PN532 nfc(sselPin);
//==============================================================================
const uint8_t teamSize = 3;
uint8_t numberOfMissions = 5;
uint8_t missionSuccessCounter = 0;
uint8_t survivalThreshold = 3;
//==============================================================================
uint8_t zombieGroup;
//==============================================================================
void setup(void)
{
  //----------------------------------------------------------------------------
  Serial.begin(9600);  // has to be fast to dump the entire memory contents!
  waitForSerial();
  //----------------------------------------------------------------------------
  setupReader();
  setupZombieGame();
  //----------------------------------------------------------------------------
}
//==============================================================================

void loop(void)
{
  for (int mission = 0; mission < numberOfMissions; mission++)
  {
    if (isMissionSuccess())
    {
      Serial.println("Mission Succeeded!");
      missionSuccessCounter++;
    }
    else
    {
      Serial.println("Oh No! Zombies, mission failed");
    }
  }
  //  if (missionSuccessCounter >= survivalThreshold)
  //  {
  //    Serial.println("Humans Win");
  //  }
  //  else
  //  {
  //    Serial.println("Zombies Win");
  //  }
  //  haltFirmware();
}
