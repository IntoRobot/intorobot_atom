/**
 ******************************************************************************
 * @file    serial_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
 */

#include "../application.h"


/*==================================================================================
名称:uint8_t EEPROM.read(int address)
参数:读取地址(目前支持0-99Byte)
返回:返回读到的数据
描述:
		通过此接口可从flash模拟的eeprom中读取数据
===================================================================================*/


/*==================================================================================
名称:void EEPROM.read(int address, uint8_t value)
参数:写入地址(目前支持0-99Byte)	写入数据 
描述:
		通过此接口可从flash模拟的eeprom中写入数据
===================================================================================*/


void setup_eeprom_test_01()
{  
	SerialUSB.begin(115200);
	//for (int i = 0; i < 512; i++)	EEPROM.write(i, 0);
	
}

void loop_eeprom_test_01()
{  
	//static unsigned int test_count=1;		//只执行一次标记
	unsigned char temp;


	//if(test_count==1)
	{
		//test_count=0;
		
		SerialUSB.print("\n===============loop_eeprom_test_01=====================");	
		
		//给0-99单元分别写入数据(可以通过一次写入之后并注释此行测试)
		for (unsigned char i = 0; i < 100; i++) EEPROM.write(i, i);	//给

		//读出数据并进行比对，如果出现不一致则打印并退出
		for (unsigned char i = 0; i < 100; i++)	
		{
			temp = EEPROM.read(i);
			SerialUSB.print(temp, DEC); 
			SerialUSB.print("\t");

			if(temp!=i)
			{
				SerialUSB.print("\n===============error====================");
				SerialUSB.print("\n==hope:");
				SerialUSB.print(i, DEC);
				SerialUSB.print("=");
				SerialUSB.print(i, DEC);  
				
				SerialUSB.print("\n==actual:");
				SerialUSB.print(i, DEC);  
				SerialUSB.print("=");
				SerialUSB.print(temp, DEC); 	
				break;
			}

			if(i==99)	
			{
				SerialUSB.print("\n===============SUCCEED====================");
				SerialUSB.print("\n===============STOP====================");
			}
			
		}
		
		
		
		
	}

}






