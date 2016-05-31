

#include "yl38.h"

/**********
土壤湿度传感器
**********/


YL38::YL38(u16 pin)
{
    _pin = pin;
}

void YL38::begin(void)
{
   pinMode(_pin,AN_INPUT);
}

u32 YL38::Read(void)
{
    return analogRead(_pin);
}


u8 YL38::CalculateHumidity(void) // 3.3V 供电
{
	soilHumidity = Read();

	if(soilHumidity < 1990)
	{
		return 100;
	}
	else if(soilHumidity >= 3970)
	{
		return 0;
	}
	else
	{
		return (u8)((3970-soilHumidity)/20);
	}
}





