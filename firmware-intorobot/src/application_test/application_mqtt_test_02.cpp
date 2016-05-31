/**
 ******************************************************************************
 * @file     : application.cpp
 * @author   : robin
 * @version  : V1.0.0
 * @date     : 6-December-2014
 * @brief    :   
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */
#if 0
#include "application.h"


TcpClient tcpclient;
system_tick_t timer_id;
uint8_t temperature;

u32 TimerGetId(void)
{
    return millis();
}

bool TimerIsEnd(u32 TimerID, u32 time)
{
    system_tick_t current_millis = millis();
    long elapsed_millis = current_millis - TimerID;
    
    //Check for wrapping
    if (elapsed_millis < 0)
    {
        elapsed_millis = TimerID + current_millis;
    }
    
    if (elapsed_millis >= time)
    {
        return true;
    }
    return false;
}

PubSubClient psclient((char *)"143.89.46.81", 1885, tcpclient );

/*******************************************************************************
 * Function Name  : void loop_mqtt
 * Description    : mqtt main loop
 * Input          : 
 * Output         : 
 * Return         : 
 *******************************************************************************/
void loop_mqtt()
{
    psclient.loop();
}

//
void PubSubcallback(char * topic, unsigned char * payload, unsigned int len)
{
    char tmp[128];
    
    if(!strcmp(topic,"v1/xyzw123/channel/light/cmd/switch"))
    {
        if(!memcmp(payload,"1",1))
        {
            digitalWrite(13, HIGH);// Turn ON the LED pins  
            psclient.publish("v1/xyzw123/channel/light/data/state", (uint8_t *)"1", 1, true);
            
        }
        else if(!memcmp(payload,"0",1))
        {
            digitalWrite(13, LOW);// Turn ON the LED pins  
            psclient.publish("v1/xyzw123/channel/light/data/state", (uint8_t *)"0", 1, true);
        }
    }
    else if(!strcmp(topic,"v1/xyzw123/firmware/update/cmd/flash"))
    {
        if(len)
        {
            digitalWrite(13, HIGH);// Turn ON the LED pins  
            memset(tmp,0,sizeof(tmp));
            memcpy(tmp,payload,len);
            psclient.publish("v1/xyzw123/firmware/update/data/state", (uint8_t *)"succeed", strlen("succeed"), true);
        }
        else
        {
            digitalWrite(13, LOW);// Turn ON the LED pins  
            psclient.publish("v1/xyzw123/firmware/update/data/state", (uint8_t *)"failed", strlen("failed"), true);
        }
    }
    return; 
}

//
void setup_mqtt_test_02()
{  
    //start serialUSB
    SerialUSB.begin(115200);
    while (!SerialUSB); // wait for a serial connection

    SerialUSB.print("bridge begin!!\r\n");

    pinMode(13, OUTPUT);  
    digitalWrite(13, LOW);// Turn ON the LED pins  

    //start bridge
    Bridge.begin();

    RGB.control(true);
    //connect mqtt broker 
    if(psclient.connect("xyzw123", "acc_chenkaiyao", "chenkaiyao", "v1/xyzw123/system/will/data/accident", 2, false, "device off-line"))
    {
        psclient.publish("v1/xyzw123/system/state/data/onoff", (uint8_t *)"hello",strlen("hello"),true);
        psclient.subscribe("v1/xyzw123/channel/light/cmd/switch", PubSubcallback, 1);
        psclient.subscribe("v1/xyzw123/firmware/update/cmd/flash", PubSubcallback, 1);
        SerialUSB.print("mqtt connected!!\r\n");
    }
    else
    {
        SerialUSB.print("mqtt not connected!!\r\n");
    }
    
    timer_id=TimerGetId();
    RGB.color(255, 255, 255);
    temperature=20;
}

void loop_mqtt_test_02()
{
    char tmp[20];

    if(TimerIsEnd(timer_id, 3000))
    {
        memset(tmp,0,sizeof(tmp));
        sprintf(tmp, "%d", temperature);
        psclient.publish("v1/xyzw123/channel/sensor/data/temperature", (uint8_t *)tmp,strlen(tmp),true);
        timer_id=TimerGetId();
        temperature+=20;
        if(temperature>160)
        {temperature=20;}
    }
}

#endif

