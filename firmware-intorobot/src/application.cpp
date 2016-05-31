/*
************************************************************************
* @author  :  IntoRobot Team
* @version :  V1.0.0
* @date    :  11-2-15
************************************************************************
 This application example code is in the public domain.

 Test for rosserial publsher
*/
/*
#include "ros.h"
#include "std_msgs/String.h"

ros::NodeHandle nh;

std_msgs::String str_msg;
ros::Publisher chatter("chatter", &str_msg);

char *rosSrvrIp = "192.168.8.216:11411";
char hello[13] = "Hello ROS!";
IntoRobotSTM32Hardware *hardware_;

void setup()
{
  nh.initNode(rosSrvrIp);
  hardware_ = nh.getHardware();
  nh.advertise(chatter);
}

void loop()

{
   str_msg.data = hello;
   chatter.publish(&str_msg);
   nh.spinOnce();
   if(hardware_->connected())
     SerialUSB.println("connected");
   else{
     SerialUSB.println("disconnected");
     nh.initNode(rosSrvrIp);
   }
   delay(10);
}*/

/*This #include statement was automatically added by the IntoRobot IDE.*/
#include "extend/WidgetSmartLight.h"
WidgetSmartLight smartLight;
WidgetSmartLight smartLight1(1);
void smartLightSwitchCb()
{
    if(smartLight.getSwitch()==1)
    {
        smartLight.control(D7,HIGH);
    }
    else
    {
        smartLight.control(D7,LOW);
    }
}

void smartLightSwitchCb1()
{
    if(smartLight1.getSwitch()==1)
    {
        smartLight1.control(D8,HIGH);
    }
    else
    {
        smartLight1.control(D8,LOW);
    }
}
void setup()
{
   smartLight.begin(smartLightSwitchCb);
   smartLight1.begin(smartLightSwitchCb1);
}

void loop()
{
delay(2000);
}
