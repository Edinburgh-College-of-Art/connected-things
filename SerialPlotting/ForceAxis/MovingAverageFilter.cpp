#include "MovingAverageFilter.h"

//==============================================================================
MovingAverageFilter::MovingAverageFilter(const uint8_t sizeOfWindow)
{
  windowSize = sizeOfWindow;
  window = new int[windowSize];
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
int MovingAverageFilter::process(int data)
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
