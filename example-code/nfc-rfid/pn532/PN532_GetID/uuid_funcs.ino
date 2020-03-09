bool isUuidInList(uint32_t testUuid, uint32_t* uuidList, uint8_t listLength)
{
  bool inList = false;
  for (int i = 0; i < listLength; i++)
  {
    if (uuidList[i] == testUuid)
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
  Serial.print("adding to list uid: ");
  Serial.print("0x");
  Serial.print(newUuid, HEX);
  idList[idIndex] = newUuid;
  idIndex++;
  idIndex %= numUuids;
}
