#include "MovingAverageFilter.h"

//==============================================================================
MovingAverageFilter::MovingAverageFilter(const uint8_t sizeOfWindow)
{
  windowSize = sizeOfWindow;
  window = new unsigned long long[windowSize];
  for (int i = 0; i < windowSize; ++i)
  {
    window[i] = 0;
  }
}
//==============================================================================
MovingAverageFilter::~MovingAverageFilter()
{
  delete[] window;
}
//==============================================================================
int MovingAverageFilter::process(unsigned long long data)
{
  window[currentIndex] = data;
  average = 0;
  for (int i = 0; i < windowSize; ++i)
  {
    average += window[i];
  }
  average /= windowSize;
  currentIndex++;
  currentIndex %= windowSize;
  return average;
}
//==============================================================================

int MovingAverageFilter::getCurrentAverage()
{
  return this->average;
}
