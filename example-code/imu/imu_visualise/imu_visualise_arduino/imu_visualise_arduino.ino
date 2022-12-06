/*
  IMU Serial:

  Send IMU (accelerometer and gyroscope) data over Serial as raw bytes.

  Libraries:

  You will need to install the Arduino_LSM6DS3 library via the library manager
  before uploading.
*/
//----------------------------------------------------------------------------
#include <Arduino_LSM6DS3.h>
#include <MadgwickAHRS.h>
#include "IMUfilter.h"
Madgwick filter;
unsigned long microsPerReading, microsPrevious;
float accelScale, gyroScale;

IMUfilter imuFilter(0.1, 10);
//----------------------------------------------------------------------------
const bool DEBUG = false;
//----------------------------------------------------------------------------
float ax = 0, ay = 0, az = 0, gx = 0, gy = 0, gz = 0;
bool updateOutput = false;
//----------------------------------------------------------------------------
void setup()
{
  filter.begin(25);
  Serial.begin(9600);
  while (!Serial);
  
  if (!IMU.begin())
  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }

  if (DEBUG)
  {
    printImuInfo();
  }
}
//----------------------------------------------------------------------------
void loop()
{
  
  if (DEBUG)
  {
    printImuData();
  }
  else
  {
    if (IMU.accelerationAvailable())
    {
      IMU.readAcceleration(ax, ay, az);
      updateOutput = true;
    }
    if (IMU.gyroscopeAvailable())
    {
      IMU.readGyroscope(gx, gy, gz);
      updateOutput = true;
    }

    if (updateOutput)
    {
      filter.updateIMU(gx, gy, gz, ax, ay, az);
      imuFilter.updateFilter(gx*0.01745329252, gy*0.01745329252, gz*0.01745329252,
                             ax* 9.78033, ay* 9.78033, az* 9.78033);
      imuFilter.computeEuler();
      
      writeFloatBytesToSerial();
      while (Serial.available() == 0)
      {
        if (IMU.accelerationAvailable())
        {
          IMU.readAcceleration(ax, ay, az);
        }
        if (IMU.gyroscopeAvailable())
        {
          IMU.readGyroscope(gx, gy, gz);
        }
      }

      while (Serial.available())
      {
        Serial.read();
      }

      updateOutput = false;
    }
  }
}
//----------------------------------------------------------------------------
