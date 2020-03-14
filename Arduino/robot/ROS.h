#include <ros.h>
#include <std_msgs/String.h>

ros::NodeHandle  nh;
std_msgs::String str_msg;
ros::Publisher sensor("sensor", &str_msg);

  
void msg_cb(const std_msgs::String& cmd_msg)
{
  if(cmd_msg.data == "a")      maju(40);
  else if(cmd_msg.data == "b") mundur(40);
  else if(cmd_msg.data == "c") kiri(60);
  else if(cmd_msg.data == "d") kanan(60);
  else if(cmd_msg.data == "e") belokKanan(40);
  else if(cmd_msg.data == "f") belokKiri(40);
  else if(cmd_msg.data == "g") rotasiKanan(40);
  else if(cmd_msg.data == "h") rotasiKiri(40);
  else if(cmd_msg.data == "i") berhenti();
}

ros::Subscriber<std_msgs::String> sub("motor", msg_cb);
