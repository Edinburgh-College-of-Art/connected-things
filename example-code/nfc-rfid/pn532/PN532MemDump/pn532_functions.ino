void setupReader()
{
  Serial.println("Looking for PN532...");
  nfc.begin();
  uint32_t versiondata = nfc.getFirmwareVersion();
  if (! versiondata)
  {
    Serial.print("Didn't find PN53x board");
    haltFirmware();
  }

  Serial.print("Found chip PN5"); Serial.println((versiondata >> 24) & 0xFF, HEX);
  printVersionNumber(versiondata);

  nfc.SAMConfig();
}

void printVersionNumber(uint32_t &versiondata)
{
  Serial.print("Firmware ver. ");
  Serial.print((versiondata >> 16) & 0xFF, DEC);
  Serial.print('.');
  Serial.println((versiondata >> 8) & 0xFF, DEC);
}

void memoryDumpCard()
{
  uint8_t success;                          // Flag to check if there was an error with the PN532
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
  uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
  uint8_t currentblock;                     // Counter to keep track of which block we're on
  bool authenticated = false;               // Flag to indicate if the sector is authenticated
  uint8_t data[16];                         // Array to store block data during reads
  uint8_t keyuniversal[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
//  uint8_t keyuniversal[6] {0XFF, 0XFF, 0XFF, 0XFF, 0XFF, 0XFF};
//  uint8_t keyuniversal[6] {0XD3, 0XF7, 0XD3, 0XF7, 0XD3, 0XF7};
//  uint8_t keyuniversal[6] {0XA0, 0XA1, 0XA2, 0XA3, 0XA4, 0XA5};
//  uint8_t keyuniversal[6] {0XB0, 0XB1, 0XB2, 0XB3, 0XB4, 0XB5};
//  uint8_t keyuniversal[6] {0X4D, 0X3A, 0X99, 0XC3, 0X51, 0XDD};
//  uint8_t keyuniversal[6] {0X1A, 0X98, 0X2C, 0X7E, 0X45, 0X9A};
//  uint8_t keyuniversal[6] {0XAA, 0XBB, 0XCC, 0XDD, 0XEE, 0XFF};
//  uint8_t keyuniversal[6] {0X00, 0X00, 0X00, 0X00, 0X00, 0X00};
//  uint8_t keyuniversal[6] {0XAB, 0XCD, 0XEF, 0X12, 0X34, 0X56};

  //----------------------------------------------------------------------------
  success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  if (success)
  {
    pinMode(6, OUTPUT);
    tone(6, 3000, 100);
    Serial.println("Found an ISO14443A card"); // Display some basic information about the card
    Serial.print("  UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
    Serial.print("  UID Value: ");
    nfc.PrintHex(uid, uidLength);
    Serial.println("");

    if (uidLength == 4)
    {
      Serial.println("Seems to be a Mifare Classic card (4 byte UID)"); // We probably have a Mifare Classic card ...

      for (currentblock = 0; currentblock < 64; currentblock++) // Now we try to go through all 16 sectors (each having 4 blocks)
      {
        if (nfc.mifareclassic_IsFirstBlock(currentblock))
        {
          authenticated = false;         // Check if this is a new block so that we can reauthenticate
        }

        if (!authenticated)    // If the sector hasn't been authenticated, do so first
        {
          Serial.print("------------------------Sector "); Serial.print(currentblock / 4, DEC); Serial.println("-------------------------");
          success = nfc.mifareclassic_AuthenticateBlock (uid, uidLength, currentblock, 1, keyuniversal);

          if (success)
          {
            authenticated = true;
          }
          else
          {
            Serial.println("Authentication error");
          }
        }

        if (!authenticated)         // If we're still not authenticated just skip the block
        {
          Serial.print("Block "); Serial.print(currentblock, DEC); Serial.println(" unable to authenticate");
        }
        else
        {
          success = nfc.mifareclassic_ReadDataBlock(currentblock, data);  // Dump the data into the 'data' array
          if (success)
          {
            Serial.print("Block "); Serial.print(currentblock, DEC);
            if (currentblock < 10)
            {
              Serial.print("  ");
            }
            else
            {
              Serial.print(" ");
            }

            nfc.PrintHexChar(data, 16);  // Dump the raw data
          }
          else
          {
            Serial.print("Block "); Serial.print(currentblock, DEC);
            Serial.println(" unable to read this block");
          }
        }
      }
    }
    else
    {
      Serial.println("Ooops ... this doesn't seem to be a Mifare Classic card!");
    }
  }
}
