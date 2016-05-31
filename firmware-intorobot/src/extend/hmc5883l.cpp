

#include "hmc5883l.h"

/**********
electronic compass
**********/



HMC5883L::HMC5883L()
{
	deviceAddress = HMC5883L_ADDRESS;
}

void HMC5883L::begin(void)
{
	
	I2Cdev::writeByte(MPU6050_DEFAULT_ADDRESS, 0x6a, 0x00); // 不使能 6050 I2C主机功能

	I2Cdev::writeByte(MPU6050_DEFAULT_ADDRESS, 0x37, 0x02); // 使能 6050的 AUX-I2C功能 使 stm32 直接访问 HMC5883L

	delay(10);

	I2Cdev::writeByte(deviceAddress, REGISTER_A, 0x70);
	I2Cdev::writeByte(deviceAddress, REGISTER_B,  0xA0);
	I2Cdev::writeByte(deviceAddress, MODE_REGISTER, 0x00);
}


void HMC5883L::GetData(int16_t* cx, int16_t* cy, int16_t* cz) 
{
    I2Cdev::readBytes(deviceAddress, X_MSB, 6, buffer,100);

    *cx = (((int16_t)buffer[0]) << 8) | buffer[1];
    *cz = (((int16_t)buffer[2]) << 8) | buffer[3];
    *cy = (((int16_t)buffer[4]) << 8) | buffer[5];

}


u16 HMC5883L::AngleCalculation(void) // 0-360°
{
	GetData(&compass_x,&compass_y,&compass_z);

	angle = atan2((double)compass_y,(double)compass_x)*(180/3.14159265)+180;

	return (u16)angle;
}

