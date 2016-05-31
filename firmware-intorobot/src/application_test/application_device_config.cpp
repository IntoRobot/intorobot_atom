/**
 ******************************************************************************
 * @file    serial_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
 */

#include "application.h"
#include "device_config.h"

//UsbDeviceConfig DeviceConfigUsb;
//TcpDeviceConfig DeviceConfigTcp;

void setup_device_config_test() {
    SerialUSB.begin(115200);

    // Bridge startup
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Bridge.begin();
    digitalWrite(13, HIGH);

    SerialUSB.print("deviceconfigtcp init....");
    DeviceConfigTcp.init();
}

void loop_device_config_test() 
{
    DeviceConfigTcp.process();
}


