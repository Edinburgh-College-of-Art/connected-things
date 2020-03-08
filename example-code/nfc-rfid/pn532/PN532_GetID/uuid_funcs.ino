bool isUuidInList(uint32_t testUuid)
{
  bool inList = false;
  for (int i = 0; i < numUuids; i++)
  {
    if(idList[i] == testUuid)
    {
      inList = true;
      break;
    }
  }
  return inList;
}

void addToList(uint32_t newUuid)
{
  idList[idIndex] = newUuid;
  idIndex++;
  idIndex%=numUuids;
}
