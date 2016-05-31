

#ifndef MQ2_H_
#define MQ2_H_

#include "application.h"



// 烟雾传感器 AD采集

class MQ2
{
	public:
	MQ2(u16 pin);
	void begin(void);
	u32 Read(void);

	private:
	u16 _pin;
};


#endif 

