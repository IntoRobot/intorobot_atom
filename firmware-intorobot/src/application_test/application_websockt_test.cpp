/**
 ******************************************************************************
 * @file    serial_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
 */
#if 0
#include "application.h"



void setup_websock_test_getpid_01()
{  

//	Serial1.begin(115200);
//	Serial1.println("setup_websock_test_getpid_01");
	
//	Bridge.begin();
	
}



//查看WiFi连接状态
void loop_websock_test_getpid_01()
{  

//	#define CMD "cat"
//	#define PRAM "/proc/mtd"


	static int run_flag=1;

	if(run_flag==1)
	{
		run_flag=0;

		wsclient.connect((char *)"ws://143.89.46.81",9876,0,(char *)"/v1/websocket/?feed_id=53dde5e6a52633d704000003&format=json&isFront=True");
	//	wsclient.getPids();		
	}
	wsclient.monitor();

	char *p_send=(char *)"websockt client 1";
	int len=strlen(p_send);

	
	wsclient.send(p_send,len);

}
#endif




