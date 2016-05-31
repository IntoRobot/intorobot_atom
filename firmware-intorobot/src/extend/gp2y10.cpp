

#include "gp2y10.h"

/**********
PM2.5Öµ »Ò³¾Å¨¶È
**********/


GP2Y10::GP2Y10(u16 dustPin,u16 ledPin)
{
    _dustPin = dustPin;
    _ledPin = ledPin;
    dustVoltage = 0;
}

void GP2Y10::begin(void)
{
   pinMode(_dustPin,AN_INPUT);
   pinMode(_ledPin,OUTPUT);
   digitalWrite(_ledPin, HIGH);
   
}

void GP2Y10::Read(void)
{
	digitalWrite(_ledPin,LOW); 
	delayMicroseconds(SAMPLE_TIME);
	dustVoltage = analogRead(_dustPin); 
	delayMicroseconds(SAMPLE_TIME_2);
	digitalWrite(_ledPin,HIGH); 
	delayMicroseconds(PLUSE_TIME);
	//return dustVoltage;
}


u16 GP2Y10::CalculatedConcentration(void) // ug/m^3
{
	Read();
	return (((dustVoltage * 3.3)/4095)*0.2)*1000;
}



