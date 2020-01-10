/*
  AirQuality library v1.0
  2010 Copyright (c) Seeed Technology Inc.  All right reserved.

  Original Author: Bruce.Qin

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
#include"Arduino.h"
#include"AirQuality.h"


//==============================================================================
/** Get the avg voltage in 5 minutes. */
void AirQuality::avgVoltage()
{
  if (averaging_count == 150) // sum 5 minutes
  {
    vol_standard = temp / 150;
    temp = 0;
    Serial.print("Vol_standard in 5 minutes:");
    Serial.println(vol_standard);
    averaging_count = 0;
  }
  else
  {
    temp += first_vol;
    averaging_count++;
  }
}

//==============================================================================
/** Initialise Air Quality Sensor */
void AirQuality::init(int pin)
{
  _pin = pin;
  pinMode (_pin, INPUT);
  Serial.println("Please Wait for a moment while the sensor warms up");
  delay(20000);
  init_voltage = analogRead(_pin);
  Serial.println("The initial voltage is ...");
  Serial.println(init_voltage);

  unsigned char i = 0;
  while (init_voltage)
  {
    if (init_voltage < 798 && init_voltage > 10) // the init voltage is ok
    {
      first_vol = analogRead(_pin); //initialize first value
      last_vol = first_vol;
      vol_standard = last_vol;
      Serial.println("Sensor ready.");
      error = false;;
      break;
    }
    else if (init_voltage > 798 || init_voltage <= 10)
    {
      i++;
      delay(10000);
      Serial.println("Waiting to Initialise Sensor..");
      init_voltage = analogRead(_pin);
      if (i == 5)
      {
        i = 0;
        error = true;
        Serial.println("Sensor Error!");
      }
    }
    else
    {
      break;
    }
  }
  Serial.println("Test begin...");
}

//==============================================================================

uint8_t AirQuality::slope(void)
{
  uint8_t result;
  if (first_vol > 700)
  {
    result = 0;
  }
  else if ( (first_vol > 300  && first_vol < 700)
            || (first_vol - vol_standard) > 150)
  {
    result = 1;
  }
  else if ((first_vol > 200 && first_vol < 300)
           || (first_vol - vol_standard) > 50)
  {
    result = 2;
  }
  else
  {
    result = 3;
  }
  avgVoltage();
  return result;
}


//==============================================================================
