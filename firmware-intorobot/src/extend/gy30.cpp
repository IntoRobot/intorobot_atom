

#include "gy30.h"

/**********
土壤湿度传感器
**********/


GY30::GY30()
{
    devAddress = GY30_ADDRESS;
}

void GY30::begin(void)
{
  	Write(0x01);
}

float GY30::Read(void)
{
	u8 i;

	Write(0x01);
	Write(0x10);

	delay(180);
	
    Wire.beginTransmission(devAddress); // ID

    //Wire.write(regAddress); // 寄存器地址

    //Wire.endTransmission(0); // 不发送停止位 但是发送 ID 和寄存器地址

    //Wire.beginTransmission(devAddr);

    Wire.requestFrom(devAddress, 2);

    for(i = 0; i < 2; i++)
    {
        dat[i] = Wire.read();
    }
    
 	lxData = dat[0];
 	
    lxData=(lxData << 8)+dat[1];//合成数据 
    
    return (float)lxData/1.2;
}

void GY30::Write(u8 regAddress)
{
    Wire.beginTransmission(devAddress);

    Wire.write(regAddress); // send address

    Wire.endTransmission();
}





