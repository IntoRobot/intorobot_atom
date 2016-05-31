

/**********
土壤湿度传感器
**********/

#ifndef YL38_H_
#define YL38_H_

#include "application.h"


// 土壤湿度传感器 AD采集

class YL38
{
	public:
		
	YL38(u16 pin);
	void begin(void);
	u32 Read(void);
	u8 CalculateHumidity(void);

	private:
	u16 _pin;
	u32 soilHumidity;
};


#endif 

