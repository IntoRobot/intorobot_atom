/**
 ******************************************************************************
 * @file    rgb_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
 */

#include "application.h"



void setup_rgb_test_01()
{  
    SerialUSB.begin(115200);
    while (!SerialUSB); // wait for a serial connection

    SerialUSB.print("rgb-test-begin\r\n");
    Bridge.begin();
    RGB.control(true);
}



//查看WiFi连接状态
void loop_rgb_test_01()
{  
    SerialUSB.print("rgb-test-color\r\n");
    RGB.color(255, 0, 0);
    delay(1000);
    RGB.color(0, 255, 0);
    delay(1000);
    RGB.color(0, 0, 255);
    delay(1000);
    RGB.color(255, 255, 255);  
    delay(1000);
    
    SerialUSB.print("rgb-test-blink\r\n");
    RGB.blink(255, 0, 0, 100); 
    delay(3000);
    RGB.blink(255, 255, 255, 100); 
    delay(3000);

    SerialUSB.print("rgb-test-breath\r\n");
    RGB.breath(255, 0, 0, 1000); 
    delay(5000);
    RGB.breath(255, 255, 255, 1000); 
    delay(5000);
}

