

#ifndef GP2Y10_H_
#define GP2Y10_H_

#include "application.h"

// 脉冲周期时间是10 ms  LED脉冲时间是320us 其中采样 280us 40us
#define		SAMPLE_TIME		280 // us
#define 	SAMPLE_TIME_2	40
#define     PLUSE_TIME		9680


// 空气灰尘传感器 AD采集

class GP2Y10
{
	public:
	GP2Y10(u16 dustPin,u16 ledPin);
	void begin(void);
	void Read(void);
	
	u16 CalculatedConcentration(void);

	private:
	u16 _dustPin;
	u16 _ledPin;
	u32 dustVoltage;
	
};


#endif 

