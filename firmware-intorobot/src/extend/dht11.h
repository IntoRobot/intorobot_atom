

#ifndef DHT_H_
#define DHT_H_

#include "application.h"

// 温湿度传感器 单线传输

class DHT11
{
	
	public:
		
	DHT11(u16 pin);
	void begin(void);
	void StartSignal(void);

	char ReadTemperature(bool s);
	u8 ReadHumidity(void);

	char ConvertCtoF(char c); // 将摄氏度转为华氏度
	char ConvertFtoC(char f);

	boolean Read(void);
	
	private:
		
	u16 _pin;
	u8  data[5];
	u32 lastReadTime;
	boolean firstReading; 
	
};

#endif 

