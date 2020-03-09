#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>
//------------------------------------------------------------------------------------
#define PN532_SS   (10)
Adafruit_PN532 nfc(PN532_SS);
//------------------------------------------------------------------------------------
void setup(void)
{
  while (!Serial);
  Serial.begin(9600);

  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata)
  {
    Serial.print("Didn't find PN53x board");
    while (1); // halt
  }
  // Got ok data, print it out!
  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  Serial.print("Firmware ver. "); Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.'); Serial.println((versiondata >> 8) & 0xFF, DEC);

  // configure board to read RFID tags
  nfc.SAMConfig();

  Serial.println("Waiting for an ISO14443A Card ...");
}
//------------------------------------------------------------------------------------
void loop(void)
{
  uint8_t uid[7];
  uint8_t uidLength;

  uint8_t success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);

  if (success)
  {
    nfc.PrintHex(uid, uidLength);
    Serial.println();

    if (uidLength == 4)
    {
      uint8_t keya[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
      success = nfc.mifareclassic_AuthenticateBlock(uid, uidLength, 4, 0, keya);

      if (success)
      {
        uint8_t data[16];
        success = nfc.mifareclassic_ReadDataBlock(4, data);

        if (success)
        {
          Serial.print("Reading Block 4:\t");
          nfc.PrintHexChar(data, 16);
          Serial.println();
        }
        else
        {
          Serial.println("Ooops ... unable to read the requested block.  Try another key?");
        }
      }
      else
      {
        Serial.println("Ooops ... authentication failed: Try another key?");
      }
    }
    delay(1000);
  }
}
