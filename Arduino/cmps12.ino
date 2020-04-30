/*****************************************
*     CMPS12 I2C example for Arduino     *
*        By James Henderson, 2014        * 
*****************************************/

#include <Wire.h>

#define CMPS12_ADDRESS 0x60  // Address of CMPS12 shifted right one bit for arduino wire library
#define ANGLE_8  1           // Register to read 8bit angle from

unsigned char high_byte, low_byte, angle8;
char pitch, roll;
unsigned int angle16;

void setup()
{
  Serial.begin(9600);  // Start serial port
  Wire.begin();
}

void loop()
{

  Wire.beginTransmission(CMPS12_ADDRESS);  //starts communication with CMPS12
  Wire.write(ANGLE_8);                     //Sends the register we wish to start reading from
  Wire.endTransmission();
  Wire.requestFrom(CMPS12_ADDRESS, 5);       
  
  while(Wire.available() < 5);        // Wait for all bytes to come back
  
  angle8 = Wire.read();               // Read back the 5 bytes
  high_byte = Wire.read();
  low_byte = Wire.read();
  pitch = Wire.read();
  roll = Wire.read();
  
  angle16 = high_byte;                 // Calculate 16 bit angle
  angle16 <<= 8;
  angle16 += low_byte;

  String sudut = String(angle16 / 10, DEC)+"." + String(angle16 % 10, DEC);
  
  Serial.print("    angle full: ");     // Display 16 bit angle with decimal plac
  Serial.println(sudut);

  delay(100);                           // Short delay before next loop
}
