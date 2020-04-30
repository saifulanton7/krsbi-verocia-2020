//#include "cmps12.h"
#include "motor.h"
#include "ROS.h"

//char pesan[5] = "hello world!";

void setup() 
{
  //compassInit();
  nh.initNode();
  //nh.advertise(sensor);
  nh.subscribe(sub);
}

void loop() 
{
  //readAngle().toCharArray(pesan,20);
  //str_msg.data = pesan;
  //sensor.publish( &str_msg ); 
  nh.spinOnce();
  delay(1);
}
