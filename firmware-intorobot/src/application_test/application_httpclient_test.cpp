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



void setup_httpclient_test_01()
{  
    // Bridge takes about two seconds to start up
    // it can be helpful to use the on-board LED
    // as an indicator for when it has initialized
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Bridge.begin();
    digitalWrite(13, HIGH);
    SerialUSB.begin(9600);
    while (!SerialUSB); // wait for a serial connection
}



//查看WiFi连接状态
void loop_httpclient_test_01()
{  
    // Initialize the client library
    HttpClient client;
    // Make a HTTP request:
    client.get("http://arduino.cc/asciilogo.txt");
    // if there are incoming bytes available
    // from the server, read them and print them:
    while (client.available()) {
        char c = client.read();
        SerialUSB.print(c);
    }
    SerialUSB.flush();
    delay(5000);
}

