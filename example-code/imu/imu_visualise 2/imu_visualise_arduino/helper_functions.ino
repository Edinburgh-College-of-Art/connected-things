void printImuInfo()
{
  Serial.print("Accelerometer sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Acceleration in G's");
  Serial.println("X\tY\tZ");
}

void printImuData()
{
  if (IMU.accelerationAvailable())
  {
    IMU.readAcceleration(ax, ay, az);

  }

  if (IMU.gyroscopeAvailable())
  {
    IMU.readGyroscope(gx, gy, gz);


  }
  Serial.print(ax);
  Serial.print('\t');
  Serial.print(ay);
  Serial.print('\t');
  Serial.println(az);
//  Serial.print(gx);
//  Serial.print('\t');
//  Serial.print(gy);
//  Serial.print('\t');
//  Serial.println(gz);

}

void writeFloatBytesToSerial()
{
  Serial.write((byte*)&ax, 4);
  Serial.write((byte*)&ay, 4);
  Serial.write((byte*)&az, 4);
  Serial.write((byte*)&gx, 4);
  Serial.write((byte*)&gy, 4);
  Serial.write((byte*)&gz, 4);
  Serial.flush();
}

void writeRoundedFloatToSerial()
{
  Serial.write(ax);
  Serial.write(ay);
  Serial.write(az);
  Serial.write(gx);
  Serial.write(gy);
  Serial.write(gz);
  Serial.flush();
}
