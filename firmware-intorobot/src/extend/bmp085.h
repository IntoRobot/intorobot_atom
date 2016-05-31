

#ifndef BMP085_H_
#define BMP085_H_

#include <math.h>
#include "application.h"
#include "I2Cdev.h"

#define  BMP085_ADDRESS  0xee>>1

#define OSS 0

// 气压传感器 计算海拔高度 IIC通讯

class BMP085
{
	public:

	BMP085();

	void begin(void);

	s16  ReadData(u8 devAddress);

	s32 ReadTemperature(void);

	s32 ReadPressure(void);

	void CalculateTemperature_Pressure();
	
	double GetAltitude(void);

	private:
	u8 devAddr;
	s16 ac1;
	s16 ac2; 
	s16 ac3; 
	u16 ac4;
	u16 ac5;
	u16 ac6;
	s16 b1; 
	s16 b2;
	s16 mb;
	s16 mc;
	s16 md;

	s32 pressureValue;
};


#endif 

