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

 
/*==================================================================================
名称:Serial.begin
参数:1波特率	2数据位、停止位、奇偶校验
描述:
		通过此接口可初始化串口波特率、数据位位数、停止位、奇偶校验位
===================================================================================*/

/*==================================================================================
名称:Serial.end
参数:
描述:
		注销串口，下次使用需要重新begin
===================================================================================*/

/*==================================================================================
名称:SerialBridge.print
参数:打印内容
描述:
		通过串口打印字符串以及数字
===================================================================================*/

/*==================================================================================
名称:SerialBridge.println
参数:打印内容
描述:
		通过串口打印字符串以及数字最后加回车
===================================================================================*/



void setup_Serial2_test_01()
{  

	SerialBridge.begin(115200);
	
}

void loop_Serial2_test_01()
{  
	static int count_test=0; 
		
	SerialBridge.println("loop_Serial2_test println");	//println 只是自动添加回车
    	SerialBridge.print("loop_Serial2_test print");

    	SerialBridge.print("loop_Serial2_test print\n");
    	
	SerialBridge.print(count_test);       // 显示十进制
	SerialBridge.print("\t");    // tab键

	SerialBridge.print(count_test, DEC);  // 十进制显示
	SerialBridge.print("\t");    // tab键

	SerialBridge.print(count_test, HEX);  // 十六进制
	SerialBridge.print("\t");    // tab键

	SerialBridge.print(count_test, OCT);  // 显示八进制
	SerialBridge.print("\t");     // tab键

	SerialBridge.println(count_test, BIN);  // 显示二进制
	
	count_test++;
	if(count_test==100) count_test=0;

}


/*==================================================================================
名称:while (!Serial)
参数:
描述:
		查询串口初始化是否完成可用了
===================================================================================*/

/*==================================================================================
名称:SerialBridge.available() 
参数:
返回:缓冲区中可用字节数
描述:
		查询串口获取串口缓冲区中的可用数据字节数
===================================================================================*/

/*==================================================================================
名称:SerialBridge.parseInt()
参数:
返回:解析到的数字
描述:
		从字符流中解析一个整形数据遇到非数字跳过如果无数据阻塞设置如下
===================================================================================*/

/*==================================================================================
名称:SerialBridge.setTimeout(system_tick_t timeout)
参数:获取数据等待超时时间ms
描述:
		设置数据流读取等待超时时间
===================================================================================*/

/*
实际连接串口1
硬件连接:PC Rx连接串口A9	PC Tx连接串口A10
测试方法:输入三个数字以空格分开按下回车，预期打印输入数字

*/
void setup_Serial2_test_02()
{  

	SerialBridge.begin(115200);

	 while (!SerialBridge) {
	    ; // wait for serial port to connect. Needed for Leonardo only
 	 }
	  SerialBridge.setTimeout(10*1000) ;		//设置数据流读取等待超时时间

	 SerialBridge.println("lsetup_Serial2_test_02");	//println 只是自动添加回车
	 SerialBridge.println("san ge shu zi");

//	 SerialBridge.write(48);	//0的ascii码是48
	
}



void loop_Serial2_test_02()
{  
	int red,green,blue;
	
	while (SerialBridge.available() > 0) 	//获取串口缓冲区中的可用数据字节数
	{
	//	SerialBridge.println("test");
		unsigned char temp;

		red = SerialBridge.parseInt(); 	//从字符流中解析一个整形数据遇到非数字跳过

		green = SerialBridge.parseInt(); 

		blue = SerialBridge.parseInt(); 
		
	
		if ((temp=SerialBridge.read()) == 13) 	//从串口缓冲区获取一个字节数据unsigned char   13是回车ascii
		{
			SerialBridge.println(red);
			SerialBridge.println(green);
			SerialBridge.println(blue);
		}
		else
		{
			SerialBridge.println(temp);
		}
	}


}


/*==================================================================================
名称:Serial.find()
参数:
返回:true/flase
描述:
		从串口buffer搜索内容
===================================================================================*/

/*==================================================================================
名称:Serial.findUntil(target, terminal)
参数:
返回:true/flase
描述:
		从串口buffer指定长度内搜索内容
===================================================================================*/




