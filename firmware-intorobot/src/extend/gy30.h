

#ifndef GY30_H_
#define GY30_H_

// 光照强度 

#include "application.h"


#define   GY30_ADDRESS 	0x46 >> 1


// 光照强度传感器 IIC通讯 D8(SDA) D9(SCL)

class GY30
{
	public:
	GY30();
	void begin(void);
	float Read(void);

	void Write(u8 regAddress);

	private:
	u8 devAddress;
	u8 dat[2];
	u16 lxData;
};


#endif 

