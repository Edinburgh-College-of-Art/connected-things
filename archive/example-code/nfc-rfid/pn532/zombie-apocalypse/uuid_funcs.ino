bool isUuidInList(uint32_t testUuid, uint32_t* uidList, uint8_t listLength)
{
  bool inList = false;
  for (int i = 0; i < listLength; i++)
  {
    if (uidList[i] == testUuid)
    {
      inList = true;
      break;
    }
  }
  return inList;
}
//==============================================================================
void addPlayer(uint32_t newUuid)
{
  static unsigned int playerIndex = 0;
  player[playerIndex] = newUuid;
  playerIndex ++;
  playerIndex  %= numPlayers;
}
