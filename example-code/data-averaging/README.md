# DATA Averaging
One of the most common problems with reading sensor data is erratic 'noisy' results. There are already examples files on house to smooth some of that noise out, but a nicer approach is to bundle the operation into a class that you can reuse over and over again.

# Moving Average Filter

A moving average filter is just a record of values that changes one data point at a time. Every time we add in a new data point, we get rid of the oldest data point. The larger the window, the smoother the average but, be aware that you lose the ability to detect sharp spikes in data changes.
This class only deals with signed integer numbers. If you are dealing with floating point data you will need to make some changes to the class in order to accommodate. This is unlikely as `analogRead()` will only return `uint16_t` integer values.

## Using the filter

To use the filter first you need to copy over the `MovingAverageFilter.h` and `MovingAverageFilter.cpp` files into your sketch folder. When you open the sketch again, those files should appear.

Then, make sure to include the library by typing `#include MovingAverageFilter.h` at the top of your sketch.

You then need to create an instance of the object.

```c++
uint8_t windowSize = 10;  // average over 10 data points
MovingAverageFilter filter(windowSize);
```

There are then two functions that you will want to use

## `MovingAverageFilter::process(int data)`

Adds a new data point to the moving average filter and return an averaged value given the current window state.

```c++
int averageNumber = filter.process(random(1000)); // filter random noise
```


## `MovingAverageFilter::getCurrentAverage()`

This function gets the last average calculated by the moving average filter.     

```c++
int averageNumber = filter.getCurrentAverage(); // get the last average value
```
