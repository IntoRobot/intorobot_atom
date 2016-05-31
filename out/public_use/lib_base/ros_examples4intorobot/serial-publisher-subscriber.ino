/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  11-2-15
************************************************************************
 This application example code is in the public domain.

 rosserial serial-xbee example for Intorobot-Atom
 use Serial which connected to A2(Rx) A3(Tx)
 In your own computer installed with ROS, you need to run:
 $ roscore
 $ rosrun rosserial_python serial_node.py _port:=/dev/ttyUSB0 _baud:=57600
 $ rostopic echo chatter
*/

#include "ros.h"
#include "std_msgs/String.h"

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher pub("pub", &str_msg);

char hello[13] = "Hello ROS!";
IntoRobotSTM32Hardware *hardware_;

void setup() 
{
  nh.initNode("Serial");  //default baud rate 57600
  nh.advertise(chatter);
  pinMode(D13, OUTPUT);  
}

void loop() 
{
   str_msg.data = hello;
   pub.publish(&str_msg);
   nh.spinOnce();
   
   digitalWrite(D13, HIGH);
   delay(500);
   digitalWrite(D13, LOW);
   delay(500);
}
