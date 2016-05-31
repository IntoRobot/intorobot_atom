

#include "bmp085.h"

/**********

**********/

BMP085::BMP085()
{
	devAddr = BMP085_ADDRESS;
}

void BMP085::begin(void)
{
	ac1 = ReadData(0xAA);
	ac2 = ReadData(0xAC);
	ac3 = ReadData(0xAE);
	ac4 = ReadData(0xB0);
	ac5 = ReadData(0xB2);
	ac6 = ReadData(0xB4);
	b1 =  ReadData(0xB6);
	b2 =  ReadData(0xB8);
	mb =  ReadData(0xBA);
	mc =  ReadData(0xBC);
	md =  ReadData(0xBE);
}

s16 BMP085::ReadData(u8 devAddress)
{
	u8 dat[2];
	s16 temp;
	
	I2Cdev::readBytes(devAddr,devAddress,2,dat,1000);

	temp = dat[0] << 8;
	temp = temp | dat[1];

	return temp;
	
}


s32 BMP085::ReadTemperature(void)
{
	u8 dat = 0x2e;
	
	I2Cdev::writeBytes(devAddr,0xf4,1,&dat);

	delay(10);

	return (s32)ReadData(0xf6);
}


s32 BMP085::ReadPressure(void)
{
	u8 dat = 0x34;
	s32 pressure;
	
	I2Cdev::writeBytes(devAddr,0xf4,1,&dat);

	delay(20);

	pressure =  (s32)ReadData(0xf6);

	pressure = pressure & 0x0000ffff;

	return pressure;
}


void BMP085::CalculateTemperature_Pressure(void)
{
	unsigned int ut;
	s32 up;
	
	long x1, x2, b5, b6, x3, b3, p;
	unsigned long b4, b7;

/////计算温度
	ut = ReadTemperature();	   // 读取温度

	x1 = (((long)ut - (long)ac6)*(long)ac5) >> 15;
	x2 = ((long) mc << 11) / (x1 + md);
	b5 = x1 + x2;

	ut = ((b5 + 8) >> 4); // temperature = ut/10;


// 计算气压

	up = ReadPressure();

	b6 = b5 - 4000;
	// Calculate B3
	x1 = (b2 * (b6 * b6)>>12)>>11;
	x2 = (ac2 * b6)>>11;
	x3 = x1 + x2;
	b3 = (((((long)ac1)*4 + x3)<<OSS) + 2)>>2;
	
	// Calculate B4
	x1 = (ac3 * b6)>>13;
	x2 = (b1 * ((b6 * b6)>>12))>>16;
	x3 = ((x1 + x2) + 2)>>2;
	b4 = (ac4 * (unsigned long)(x3 + 32768))>>15;
	
	b7 = ((unsigned long)(up - b3) * (50000>>OSS));
	if (b7 < 0x80000000)
	p = (b7<<1)/b4;
	else
	p = (b7/b4)<<1;
	
	x1 = (p>>8) * (p>>8);
	x1 = (x1 * 3038)>>16;
	x2 = (-7357 * p)>>16;
	
	up = p+((x1 + x2 + 3791)>>4);
	
	pressureValue = up;


}



double BMP085::GetAltitude(void)
{
	double altitude;
	CalculateTemperature_Pressure();
	s32 pressure = (float)pressureValue;				//获取气压值
	altitude = 44330.0*(1-pow((double)pressure/101325,1/5.255));  	//根据芯片手册提供的公式计算海拔高度
	//altitude*=100;	 		//转换成厘米单位的高度值，调用时再换算成带小数的高度值，提高精度



	return altitude;
}

