/*
   Visualise Pitch and Roll of Arduino
 
 - Upload imu_visualise_arduino sketch to Arduino Nano 33 IoT
 - Run this sketch
 - type in the port number
 */

import processing.serial.*;
import java.nio.*;

Serial arduino;

final int numDataPoints = 9;
float pitch, roll, yaw, lastRoll, lastPitch;
float ax, ay, az, gx, gy, gz;
PImage img;
float data[];

boolean serialPortSet = false;
int serialPortNumber;

void setup()
{
  size(400, 400, P3D);
  printArray(Serial.list());
  img = loadImage("di_logo.png");
  data = new float[numDataPoints];
  listSerialPorts();
}

void draw()
{
  if (!serialPortSet)
    return;

  updateImuData();

  //pitch = getPitch();
  //roll = getRoll();

  background(0);
  noStroke() ;

  translate(width/2, height/2, -100);

  //rotateX(roll);
  //rotateZ(-pitch);
  //rotateY(yaw);
  // pushMatrix(); // begin object

  float c1 = cos(roll);
  float s1 = sin(roll);
  float c2 = cos(pitch);
  float s2 = sin(pitch);
  float c3 = cos(yaw);
  float s3 = sin(yaw);
  applyMatrix( c2*c3, s1*s3+c1*c3*s2, c3*s1*s2-c1*s3, 0,
               -s2, c1*c2, c2*s1, 0,
               c2*s3, c1*s2*s3-c3*s1, c1*c3+s1*s2*s3, 0,
               0, 0, 0, 1);
    scale(190);
  drawBox(0.6, 0.1, 1);

  //popMatrix(); // end of object


  


}

float getPitch()
{
  if (ay * sin(roll) + az * cos(roll) == 0)
  {
    pitch = (ax > 0) ? (PI / 2) : (-PI / 2);
  } else
  {
    pitch = atan(-ax / (ay * sin(roll) + (az * cos(roll))));
  }
  return pitch;
}

float getRoll()
{
  return atan2(ay, az);
}

void drawBox(float w, float h, float d)
{
  // Front
  beginShape(QUADS) ;
  fill(255, 0, 0) ;
  vertex(-w, -h, d) ;
  vertex( w, -h, d) ;
  vertex( w, h, d);
  vertex(-w, h, d) ;
  endShape() ;

  // Back
  beginShape(QUADS) ;
  fill(255, 255, 0) ;
  vertex( w, -h, -d) ;
  vertex(-w, -h, -d);
  vertex(-w, h, -d) ;
  vertex( w, h, -d);
  endShape() ;

  // Bottom
  beginShape(QUADS);
  fill( 255, 0, 255);
  vertex(-w, h, d);
  vertex( w, h, d);
  vertex( w, h, -d);
  vertex(-w, h, -d);
  endShape();

  // Top
  blendMode(REPLACE);
  textureMode(NORMAL);
  textureWrap(CLAMP);
  beginShape(QUADS);
  texture(img);
  tint(255, 255, 255);
  vertex(-w, -h, -d, -1, -0.2);
  vertex( w, -h, -d, 2, -0.2);
  vertex( w, -h, d, 2, 1.2);
  vertex(-w, -h, d, -1, 1.2);
  endShape();

  // Right
  beginShape(QUADS);
  fill(0, 0, 255);
  vertex( w, -h, d);
  vertex( w, -h, -d);
  vertex( w, h, -d);
  vertex( w, h, d);
  endShape();

  // Left
  beginShape(QUADS);
  fill(0, 255, 0) ;
  vertex(-w, -h, -d) ;
  vertex(-w, -h, d) ;
  vertex(-w, h, d) ;
  vertex(-w, h, -d);
  endShape();
}

void updateImuData()
{
  if (arduino.available() == (4 * numDataPoints) )
  {
    for (int i = 0; i < numDataPoints; i++)
    {
      data[i] =  ByteBuffer.wrap(arduino.readBytes(4)).order(ByteOrder.LITTLE_ENDIAN).getFloat();
    }
    ax = data[0];
    ay = data[1];
    az = data[2];
    gx = data[3];
    gy = data[4];
    gz = data[5];
    roll = data[6];
    pitch= data[7];
    yaw = data[8];
    arduino.write(1);
  }
}

void listSerialPorts()
{
  background(0, 0, 0);
  text("press the number of your serial port on your keyboard", 10, 70);
  for (int i = 0; i < Serial.list().length; i++)
  {
    String port  = Serial.list()[i];
    text("["+String.valueOf(i)+"] " + port, 10, 100 + (15*i));
  }
}

void keyPressed(KeyEvent e)
{  
  if (
    e.getKeyCode() >= 48 && 
    e.getKeyCode() <= 57 && 
    !serialPortSet
    )
  {    
    serialPortNumber = e.getKeyCode() - 48;
    serialPortSet = true;
    arduino = new Serial(this, Serial.list()[serialPortNumber], 9600);
  }
}
