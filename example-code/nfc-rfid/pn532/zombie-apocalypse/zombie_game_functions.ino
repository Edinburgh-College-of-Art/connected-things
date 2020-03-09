//==============================================================================
void setupZombieGame()
{
  printTitle();
  randomSeed(analogRead(0));
  zombieGroup = random(numPlayers - 1);

  uint8_t p = 0;
  while (p < numPlayers)
  {
    Serial.print("Group:");
    Serial.print(p);
    Serial.println(" present your card");
    uint32_t newGroup = waitForCard();
    if (!isUuidInList(newGroup, player, numPlayers))
    {
      addToList(newGroup);
      writeBlock(4, (p == zombieGroup) ? "ZOMBIE" : "HUMAN ");
      p++;
    }
    else
    {
      Serial.println("Card already playing");
    }
    delay(1000);
  }

  Serial.println("All Teams Present, let's play\n");
}
//==============================================================================
uint32_t waitForCard()
{
  uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };
  uint8_t uidLength;
  uint32_t fullUuid = 0;
  uint8_t success = 0;
  while (!success) {
    success = nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength);
  }
  beep();

  for (int i = 0; i < 4; i++)
  {
    fullUuid |= (uid[i] << (8 * i));
  }
  return fullUuid;
}
//==============================================================================
boolean isMissionSuccess() // go on a mission
{
  uint32_t team[teamSize] = {0};
  setTeam(team, 3);
  return !areZombiesOnTeam(team);
}
//==============================================================================
void setTeam(uint32_t* team, uint8_t numMembers)
{
  Serial.println("Choose Your Team:");
  Serial.print("Team Size: ");
  Serial.println(teamSize);

  for (uint8_t i = 0; i < numMembers; i++)
  {
    uint32_t newGroup = waitForCard();

    if (isUuidInList(newGroup, player, numPlayers))
    {
      if (!isUuidInList(newGroup, team, teamSize))
      {
        Serial.print(newGroup);
        Serial.println(" joined the team");
        team[i] = newGroup;
      }
      else
      {
        --i;
      }
    }
    else
    {
      Serial.print(newGroup);
      Serial.println(" is not playing the game");
      --i;
    }
    delay(1000);
  }
}

//==============================================================================
bool areZombiesOnTeam(uint32_t* team)
{
  return isUuidInList(player[zombieGroup], team, 3);
}

void printTitle()
{
  const char* titleText =
    " ______                _     _         ___                        _                      \n"
    "|___  /               | |   (_)       / _ \\                      | |                     \n"
    "   / /  ___  _ __ ___ | |__  _  ___  / /_\\ \\_ __   ___   ___ __ _| |_   _ _ __  ___  ___ \n"
    "  / /  / _ \\| '_ ` _ \\| '_ \\| |/ _ \\ |  _  | '_ \\ / _ \\ / __/ _` | | | | | '_ \\/ __|/ _ \\\n"
    "./ /__| (_) | | | | | | |_) | |  __/ | | | | |_) | (_) | (_| (_| | | |_| | |_) \\__ \\  __/\n"
    "\\_____/\\___/|_| |_| |_|_.__/|_|\\___| \\_| |_/ .__/ \\___/ \\___\\__,_|_|\\__, | .__/|___/\\___|\n"
    "                                           | |                       __/ | |             \n"
    "                                           |_|                      |___/|_|             \n";
    
  Serial.println(titleText);
  Serial.println("=============================================================================================\n");
  Serial.print("Players: ");
  Serial.println(numPlayers);
  Serial.print("Team Size: ");
  Serial.println(teamSize);
  Serial.println("\n=============================================================================================\n");  
}
