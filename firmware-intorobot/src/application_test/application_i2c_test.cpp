


#include "../application.h"


#define AT24C02_ID   0x50 // 本版本的I2C会将地址左移一位

unsigned char TxBuf[10] = {0x0a,0x1,0x2,0x3,0x4,0x5,0x6,0x7,0x8,0x9};
unsigned char RxBuf[10] = {0,0,0,0,0,0,0,0,0,0};


void setup_i2c_test(void)
{
	//unsigned char i;
	//pinMode(led_test, OUTPUT);  
	//pinMode(led1_test, OUTPUT); 
	//digitalWrite(led_test, HIGH); 
	
	SerialBridge.begin(115200);
	
	Wire1.begin();
	//if(Wire1.endTransmission() == 0)
	//	Serial1.print("i2c发送成功\r\n");
	//else
	//	Serial1.print("i2c发送失败\r\n");
	/*for(i = 0; i < 10; i++)
	{
		Wire1.beginTransmission(0xa0);
		Wire1.write(TxBuf,10);
		Wire.endTransmission();
		delay(500);
	}*/
	//pinMode(11, OUTPUT);  
	//delay(500);

}

void loop_i2c_test()
{
    Wire1.beginTransmission(AT24C02_ID); // ID

    Wire1.write(0x00); // 寄存器地址
    for (uint8_t i = 0; i < 10; i++) 
    {
        Wire1.write((uint8_t) TxBuf[i]);
    }
    Wire1.endTransmission(); // 不发送停止位 但是发送 ID 和寄存器地址

	delay(20);


    Wire1.beginTransmission(AT24C02_ID); // ID

    Wire1.write(0x00); // 寄存器地址

    Wire1.endTransmission(0); // 不发送停止位 但是发送 ID 和寄存器地址

    Wire1.beginTransmission(AT24C02_ID);

    Wire1.requestFrom(AT24C02_ID, 10);

    for(uint8_t count = 0; count < 10; count++)
    {
        RxBuf[count] = Wire1.read();
    }
 	//Wire1.beginTransmission(AT24C02_ID);
	//Wire1.write(TxBuf,10);
	//Wire1.endTransmission();
	//delay(20);
	//digitalWrite(11, LOW);
	//delay(100); 
	//digitalWrite(11, HIGH);  
	//delay(100); 

	//Wire1.requestFrom(AT24C02_ID,10);
  	//while(Wire1.available())   // slave may send less than requested
	//{
	//   char c = Wire1.read(); // receive a byte as character
	//   SerialBridge.print(c);         // print the character
	//}
}
