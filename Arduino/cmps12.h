#include <Wire.h>

#define CMPS12_ADDRESS 0x60  // Address of CMPS12 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

unsigned int angle16;

void compassInit()
{
  Wire.begin();
}

String readAngle()
{
  Wire.beginTransmission(CMPS12_ADDRESS);  //starts communication with CMPS12
  Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
  Wire.endTransmission();
  Wire.requestFrom(CMPS12_ADDRESS, 5);        
  while(Wire.available() < 5);        // Wait for all bytes to come back  
  unsigned char angle8 = Wire.read();               // Read back the 5 bytes
  unsigned char high_byte = Wire.read();
  unsigned char low_byte = Wire.read();
  char pitch = Wire.read();
  char roll = Wire.read();
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;
  String sudut = String(angle16 / 10, DEC) + "." +String(angle16 % 10, DEC);
  return sudut;
}
