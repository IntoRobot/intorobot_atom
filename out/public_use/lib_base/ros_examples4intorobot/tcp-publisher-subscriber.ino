/*
************************************************************************
* @author  :  IntoRobot Team & HITSZ-NRSL
* @version :  V1.0.0
* @date    :  11-2-15
************************************************************************
 This application example code is in the public domain.

 ros tcp pub&sub example for Intorobot
 use the wifi module of IntoRobot
 In your own computer installed with ROS, you need to run:
 $ roscore
 $ rosrun rosserial_python serial_node.py tcp 
 $ rostopic echo pub
 $ rostopic pub /toggle_led std_msgs/Empty #this is used to toggle the led
*/

#include "ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"

ros::NodeHandle nh;
std_msgs::String str_msg;
ros::Publisher pub("pub", &str_msg);
char *rosSrvrIp = "192.168.8.216:11411";
char hello[35] = "Hello ROS! I am IntoRobot";
IntoRobotSTM32Hardware *hardware_;

void messageCb( const std_msgs::Empty& toggle_msg) {
  digitalWrite(D13, HIGH - digitalRead(13)); // blink the onboard LED
}
ros::Subscriber<std_msgs::Empty> sub("toggle_led", messageCb);

void setup() 
{
  pinMode(D13, OUTPUT);  
  nh.initNode(rosSrvrIp);
  hardware_ = nh.getHardware();
  nh.advertise(pub);
  nh.subscribe(sub);
}

void loop() 
{
   str_msg.data = hello;
   pub.publish(&str_msg);
   nh.spinOnce();
   if(hardware_->connected())
     SerialUSB.println("connected");
   else{
     SerialUSB.println("disconnected");
     nh.initNode(rosSrvrIp);
   }
   delay(100);
}
