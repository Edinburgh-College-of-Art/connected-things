/*
  MovingAverageFilter

  Smooth Data with a moving average filter. Integer numbers only
*/
//==============================================================================
#ifndef __MovingAverageFilter_H__
#define __MovingAverageFilter_H__
//==============================================================================
#include "Arduino.h"
//==============================================================================
class MovingAverageFilter
{
  public:
    //--------------------------------------------------------------------------
    // Methods
    /** Constructor 
    @param  sizeOfWindow  initialise with averaging window size
    */
    MovingAverageFilter(const uint8_t sizeOfWindow);
    /** Destructor */
    ~MovingAverageFilter();

    /*!
      @brief  Add a data point to the moving average filter
      
      @param  data  new data point

      @returns averaged value given the new data point and current window state
    */
    int process(int data);
    /*!
      @brief  get the last average calculated by the moving average window     

      @returns averaged value as int
    */
    int getCurrentAverage();
  private:
    //--------------------------------------------------------------------------
    // Members
    uint8_t windowSize;       // size of the moving average window. Assuming there is not a window size > 255
    int* window;              // The moving average window buffer
    uint8_t currentIndex = 0; // current index to which we will write to the buffer.
    int average = 0;          // averaged value from window
};
#endif
