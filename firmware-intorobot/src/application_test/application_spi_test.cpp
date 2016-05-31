


#include "../application.h"



unsigned char i=0;


void SendSPI_Data(unsigned char data)
{
	digitalWrite(PIN_SPI_SS, LOW);
	SPI.transfer(data);
	digitalWrite(PIN_SPI_SS, HIGH);
}


void setup_spi_test(void)
{
	
	//pinMode(led1_test, OUTPUT); 
	//digitalWrite(led_test, HIGH); 
	
	SerialBridge.begin(115200);
	
	SPI.begin();

	delay(20);

}

void loop_spi_test()
{


	for(i = 0; i < 10; i++)
	{
		SendSPI_Data(i);
		delay(1);
	}
	delay(10);
	
	/*
	digitalWrite(led1_test, LOW);
	delay(100); 
	digitalWrite(led1_test, HIGH);  
	delay(100); 
	*/

}