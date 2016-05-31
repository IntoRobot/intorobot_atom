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


extern void setup_led_test_01();
extern void loop_led_test_01();


extern void setup_Serial1_test_01();
extern void loop_Serial1_test_01();

extern void setup_Serial1_test_02();
extern void loop_Serial1_test_02();



extern void setup_Serial2_test_01();
extern void loop_Serial2_test_01();

extern void setup_Serial2_test_02();
extern void loop_Serial2_test_02();



extern void setup_Serial_test_01();
extern void loop_Serial_test_01();

extern void setup_Serial_test_02();
extern void loop_Serial_test_02();


extern void setup_pluseIn_test();
extern void loop_pluseIn_test();
extern void setup_i2c_test();
extern void loop_i2c_test();



extern void setup_eeprom_test_01();
extern void loop_eeprom_test_01();



extern void setup_shell_test_01();
extern void loop_shell_test_01();
extern char *run_shell_test(char *p_cmd,unsigned int time_out);



extern void setup_wifi_test_init_01();
extern void loop_wifi_test_get_st_01();



extern void setup_wifi_test_mdf_01();
extern void loop_wifi_test_mdf_02();


extern void loop_websock_test_getpid_01();



extern void setup_mqtt_test_02();

extern void loop_mqtt_test_02();


SYSTEM_MODE(MODE_MANUAL)
//SYSTEM_MODE(MODE_AUTOMATIC)


void setup()
{  
//setup_i2c_test();
	setup_led_test_01();
//	setup_Serial_test_02();	//硬件2
//	setup_Serial1_test_02();	//硬件3
//	setup_Serial2_test_02();	//硬件1	7620专用
	
//	setup_eeprom_test_01();

//	setup_shell_test_01();

//	setup_wifi_test_init_01();

//	 setup_wifi_test_mdf_01();

}

void loop()
{

//loop_i2c_test();
	loop_led_test_01();

//	loop_Serial_test_02();		//硬件2
//	loop_Serial1_test_02();	//硬件3
//	loop_Serial2_test_02();	//硬件1	7620专用
	
//	loop_eeprom_test_01();

//	loop_shell_test_01();

//	 loop_wifi_test_get_st_01();
//	loop_wifi_test_mdf_02();

//	loop_websock_test_getpid_01();

}

#endif
#if 1
#include "application.h"
     
     
//SYSTEM_MODE(SEMI_AUTOMATIC);
//cmd
#define CMD_LIGHTSWITCH "channel/LightSwitch_0/cmd/Switch" 

//data
#define DATA_LIGHTSTATE  "channel/LightSwitch_0/data/Light"
#define DATA_TMMPERATURE "channel/thermometerDb_0/data/thermometer"
#define DATA_WHEELSPEED  "channel/circleDb_0/data/circle_Db"


uint8_t temperature=0;
int32_t wheelspeed=0;


void LightSwitchCb(uint8_t * payload, uint32_t len)
{
    SerialUSB.println("LightSwitchCb");
    if(!memcmp(payload,"1",1))
    {
        digitalWrite(13, HIGH);// Turn ON the LED pins  
        IntoRobot.publish(DATA_LIGHTSTATE, (uint8_t *)"1", 1);

    }
    else if(!memcmp(payload,"0",1))
    {
        digitalWrite(13, LOW);// Turn ON the LED pins  
        IntoRobot.publish(DATA_LIGHTSTATE, (uint8_t *)"0", 1);
    }
}

void setup() 
{
    pinMode(13, OUTPUT);  
    IntoRobot.subscribe(CMD_LIGHTSWITCH, NULL, LightSwitchCb);
}


void loop() 
{
    char tmp[128];

    memset(tmp,0,sizeof(tmp)); // 温度
    sprintf(tmp, "%d", temperature);
    IntoRobot.publish(DATA_TMMPERATURE, (uint8_t *)tmp,strlen(tmp));

    memset(tmp,0,sizeof(tmp)); // 湿度
    sprintf(tmp, "%d", wheelspeed);
    IntoRobot.publish(DATA_WHEELSPEED, (uint8_t *)tmp,strlen(tmp));

    temperature++;
    wheelspeed++;

    IntoRobot.printf("loop tempprature:%d  wheelspeed:%d\r\n",temperature,wheelspeed);
    delay(2000);
}
#endif
