

#ifndef HMC5883L_H_
#define HMC5883L_H_


/*
hmc583l作为从机接在MPU6050上的AUX_SDA AUX_SCL
*/
#include "mpu6050.h"
#include "application.h"
#include <math.h>

#define HMC5883L_ADDRESS  0x3c >> 1

#define REGISTER_A				0x00
#define REGISTER_B				0x01
#define MODE_REGISTER			0x02
#define X_MSB					0x03
#define X_LSB					0x04
#define Z_MSB					0x05
#define Z_LSB					0x06
#define Y_MSB					0x07
#define Y_LSB					0x08
#define STATUS_REGISTER			0x09
#define DISCERN_REGISTER_A		0x10
#define DISCERN_REGISTER_B		0x11
#define DISCERN_REGISTER_C		0x12


// 电子罗盘 IIC通讯

class HMC5883L 
{
	public:

	HMC5883L();

	void begin(void);	

	void GetData(int16_t* cx, int16_t* cy, int16_t* cz);

	u16 AngleCalculation(void);

	private:

	u8 deviceAddress;
	u8 buffer[6];
	s16 compass_x;
	s16 compass_y;
	s16 compass_z;

	double angle;


	
};



#endif 

