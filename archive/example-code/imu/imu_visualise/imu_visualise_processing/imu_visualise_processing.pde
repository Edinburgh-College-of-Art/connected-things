/*
   Visualise Pitch and Roll of Arduino
 
 - Upload imu_visualise_arduino sketch to Arduino Nano 33 IoT
 - Run this sketch
 - type in the port number
 */

import processing.serial.*;
import java.nio.*;

Serial arduino;

float pitch, roll, lastRoll, lastPitch;
float ax, ay, az, gx, gy, gz;
PImage img;
float data[];
boolean serialPortSet = false;
int serialPortNumber;
float pos = 0;
float yaw = 0;

void setup()
{
  size(400, 400, P3D);
  printArray(Serial.list());
  img = loadImage("di_logo.png");
  data = new float[6];
  listSerialPorts();
}

void draw()
{
  if (!serialPortSet)
    return;

  updateImuData();

  pitch = getPitch();
  roll = getRoll();

  background(0);
  noStroke() ;

  translate(width/2, height/2, -100);


  pushMatrix();
  rotateX(roll);  
  rotateZ(-pitch);

  popMatrix();
  rotateY(PI/2);

  scale(190);

  drawBox(0.6, 0.1, 1);
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

float getYaw()
{
  yaw = 180 * atan (az/sqrt(ax*ax + az*az)) * 0.318309886;
  return yaw;
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
  if (arduino.available() == 24)
  {
    for (int i = 0; i < 6; i++)
    {
      data[i] =  ByteBuffer.wrap(arduino.readBytes(4)).order(ByteOrder.LITTLE_ENDIAN).getFloat();
    }
    ax = data[0];
    ay = data[1];
    az = data[2];
    gx = data[3];
    gy = data[4];    
    gz = data[5];
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
