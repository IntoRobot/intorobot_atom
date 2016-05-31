

#include "mq2.h"

/**********
烟雾报警器
TTL电平检测方式
AD检测方式
**********/


MQ2::MQ2(u16 pin)
{
    _pin = pin;
}

void MQ2::begin(void)
{
   pinMode(_pin,AN_INPUT);
}

u32 MQ2::Read(void)
{
    return analogRead(_pin);
}




