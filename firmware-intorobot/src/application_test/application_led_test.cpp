/**
 ******************************************************************************
 * @file    serial_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
*/

#include "../application.h"


int led_test = D13;  
//int led_test1 = 11; 

unsigned int  count_led = 0;
 
void setup_led_test_01()
{  
	pinMode(led_test, OUTPUT);  
    //pinMode(led_test1, OUTPUT);  

}


void loop_led_test_01()
{
    digitalWrite(led_test, LOW);   // Turn ON the LED pins  
    delay(300);
    digitalWrite(led_test, HIGH);   // Turn ON the LED pins  
    delay(300);
    #if 0
	if(count_led == 0)
	{
		digitalWrite(led_test, LOW);   // Turn ON the LED pins  
		//digitalWrite(led_test1, LOW);  
        //delayMicroseconds(100000);
	}


    //delay(30);
    if(count_led == 30000) 
	{
		digitalWrite(led_test, HIGH);   // Turn ON the LED pins  
		//digitalWrite(led_test1, HIGH); 
         //delayMicroseconds(100000);
	}

    
	//delay(30);
	count_led++; 
	if(count_led == 60000) 
    {
       count_led = 0;
    }
#endif
}
