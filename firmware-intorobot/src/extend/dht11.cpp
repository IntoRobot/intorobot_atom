

#include "dht11.h"


/**********************************
数据共5个字节
字节1 湿度整数
字节2 湿度小数 DTH11为0 
字节3 温度整数
字节4 温度小数 DTH11为0 
字节5 前面4个字节的和 用于校验
**********************************/


DHT11::DHT11(u16 pin)
{
    _pin = pin;
    firstReading = true;
}

void DHT11::begin(void)
{
    pinMode(_pin,OUTPUT);
    digitalWrite(_pin, HIGH);
    lastReadTime = 0;
}

void DHT11::StartSignal(void)
{
    digitalWrite(_pin,LOW);
    delay(20);
    digitalWrite(_pin,HIGH);
}

char DHT11::ConvertCtoF(char c)
{
    return (char)c * 9 / 5 + 32;
    
}

char DHT11::ConvertFtoC(char f)
{
    return (char)(f - 32) * 5 / 9;
}


char DHT11::ReadTemperature(bool s)
{
    char temp = 0;
    
    if(Read())
    {
        temp = data[2];
       
        if(s)
        {
          	temp = ConvertCtoF(temp);
        }
        
    }
	
    return temp;
}


u8 DHT11::ReadHumidity(void)
{
    u8 temp = 0;

    if(Read())
    {
        temp = data[0];
    }

    return temp;
}




boolean DHT11::Read(void)
{
     uint8_t i,timeOut = 0;
     uint8_t laststate = HIGH;
     uint8_t j = 0;

     u32 currentTime;

     currentTime = millis();

	if (currentTime < lastReadTime) 
	{
		// ie there was a rollover
		lastReadTime = 0;
	}
	if (!firstReading && ((currentTime - lastReadTime) < 2000)) 
	{
		return true; // return last correct measurement
		//delay(2000 - (currenttime - _lastreadtime));
	}
  
  	firstReading = false;

  	lastReadTime = millis();

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    noInterrupts();
     
    StartSignal();

    pinMode(_pin,INPUT_PULLUP);

    // read in timings
    for(i = 0; i < 83; i++) 
    {
        timeOut = 0;
        
        while (digitalRead(_pin) == laststate) 
        {
          timeOut++;
          delayMicroseconds(1);
          if (timeOut == 255) 
          {
             break;
          }
        }
        
        laststate = digitalRead(_pin);

        if (timeOut == 255) break;

        // ignore first 3 transitions
        if ((i >= 4) && (i%2 == 0)) // 第4个电平以及为高电平才存储数据
        {
              // shove each bit into the storage bytes
              data[j/8] <<= 1;
              
              if(timeOut > 6) // 数据 1
              {
                data[j/8] |= 1;
              }
              
              j++;
        }

    }

    pinMode(_pin,OUTPUT);
    digitalWrite(_pin,1);

	interrupts();

	
	
    if((j >= 40) && ((data[0] + data[1] + data[2] + data[3]) == data[4]))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}






