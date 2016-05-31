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
#include "application.h"


#define LIGHTSTATE  "channel/light/data/state"
#define TMMPERATURE "channel/sensor/data/temperature"
#define HUMIDITY    "channel/humidifier/data/humidity"
#define INTENSITY   "channel/smoke/data/intensity"
#define WHEELSPEED  "channel/wheel/data/speed"
#define GYROSCOPE   "channel/gyroscope/data/numbers"

system_tick_t timer_id;

uint8_t temperature=0;
uint8_t humidity=0;
int32_t smokeIntensity=0;
/*
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
    
    if (elapsed_millis >= (long)time)
    {
        return true;
    }
    return false;
}
*/

void LightSwitchCb(uint8_t * payload, uint32_t len)
{
    SerialUSB.print("LightSwitchCb");
    SerialUSB.print(payload[0]);

    if(!memcmp(payload,"1",1))
    {
        digitalWrite(13, HIGH);// Turn ON the LED pins  
        IntoRobot.publish(LIGHTSTATE, (uint8_t *)"1", 1, true);

    }
    else if(!memcmp(payload,"0",1))
    {
        digitalWrite(13, LOW);// Turn ON the LED pins  
        IntoRobot.publish(LIGHTSTATE, (uint8_t *)"0", 1, true);
    }
}

void WheelSpeedCb(uint8_t * payload, uint32_t len)
{
    SerialUSB.print("WheelSpeedCb");
   //pwmSpeed = payload[0];
}

void ScreenTextCb(uint8_t * payload, uint32_t len)
{
    SerialUSB.print("ScreenTextCb");
}

void setup() 
{

    SerialUSB.print("setup");

	pinMode(13, OUTPUT);  
    IntoRobot.subscribe("channel/light/cmd/switch", NULL, LightSwitchCb);
    IntoRobot.subscribe("channel/wheel/cmd/speed", NULL, WheelSpeedCb);
    IntoRobot.subscribe("channel/screen/data/text", NULL, ScreenTextCb);
    timer_id = TimerGetId();
}

void loop() 
{
    char tmp[128];
       
    if(TimerIsEnd(timer_id, 2000))
    {
        memset(tmp,0,sizeof(tmp)); // Êª¶È
        sprintf(tmp, "%d", humidity);
        IntoRobot.publish(HUMIDITY, (uint8_t *)tmp,strlen(tmp),true);
        
        memset(tmp,0,sizeof(tmp));  // ÑÌÎíÅ¨¶È
        sprintf(tmp, "%d", smokeIntensity);
        IntoRobot.publish(INTENSITY, (uint8_t *)tmp,strlen(tmp),true);

        memset(tmp,0,sizeof(tmp)); // ÎÂ¶È
        sprintf(tmp, "%d", temperature);
        IntoRobot.publish(TMMPERATURE, (uint8_t *)tmp,strlen(tmp),true);

        //memset(tmp,0,sizeof(tmp));  // 6050
        //sprintf(tmp, "{\"acc_x\":%f,\"gyro_x\":%f,\"acc_y\":%f,\"gyro_y\":%f}",acc_x,gy_y,acc_y,gy_y);
        //IntoRobot.publish(GYROSCOPE, (uint8_t *)tmp,strlen(tmp),true);

        temperature++;
        humidity++;
        smokeIntensity++;

        timer_id = TimerGetId();
    }
}
