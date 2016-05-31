


#include "../application.h"





void setup_time_test(void)
{

	SerialBridge.begin(115200);
	Time.setTime(100000000);
	delay(500);

}

void loop_time_test()
{
	
	SerialBridge.print(Time.timeStr());
	SerialBridge.print("\r\n");
	delay(3000);
	
	/*
	digitalWrite(led1_test, LOW);
	delay(100); 
	digitalWrite(led1_test, HIGH);  
	delay(100); 
	*/

}
