#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include <ros.h>
#include <std_msgs/UInt16.h>
#include <std_msgs/Float32MultiArray.h>

ros::NodeHandle  nh;

#include "motor.h"

void motor_cb( const std_msgs::UInt16& cmd_msg)
{
  if(cmd_msg.data == 1) maju(40);
  else if(cmd_msg.data == 2) mundur(40);
  else if(cmd_msg.data == 3) kiri(60);
  else if(cmd_msg.data == 4) kanan(60);
  else if(cmd_msg.data == 5) belokKanan(40);
  else if(cmd_msg.data == 6) belokKiri(40);
  else if(cmd_msg.data == 7) rotasiKanan(40);
  else if(cmd_msg.data == 8) rotasiKiri(40);
  else if(cmd_msg.data == 0) berhenti(); 
}

ros::Subscriber<std_msgs::UInt16> sub("motor", motor_cb);

void setup()
{
  motorInit();
  //nh.initNode();
  //nh.subscribe(sub);
}

void loop()
{
  //nh.spinOnce();
  kiri(100);
  delay(1);
}
