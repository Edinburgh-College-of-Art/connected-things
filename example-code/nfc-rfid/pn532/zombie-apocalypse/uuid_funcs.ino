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
void addToList(uint32_t newUuid)
{
  player[idIndex] = newUuid;
  idIndex++;
  idIndex %= numPlayers;
}
