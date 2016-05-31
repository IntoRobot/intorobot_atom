/**
 ******************************************************************************
 * @file    serial_test.cpp
 * @authors  lbz
 * @version V1.0.0
 * @date    2014_11_13
 * @brief   
 ******************************************************************************
 */

#include "application.h"


void setup_shell_test_01()
{  

	// Initialize Bridge
	Bridge.begin();
	
}




void loop_shell_test_01()
{  

	#define CMD "cat"
	#define PRAM "/proc/mtd"


	static int run_flag=1;

	if(run_flag==1)
	{
		run_flag=0;
		// Launch "curl" command and get Arduino ascii art logo from the network
		// curl is command line program for transferring data using different internet protocols
		Process p;		// Create a process and call it "p"
		p.begin(CMD);	// Process that launch the "curl" command
		p.addParameter(PRAM); // Add the URL parameter to "curl"
		p.run();		// Run the process and wait for its termination

		// Print arduino logo over the Serial
		// A process output can be read with the stream methods
		while (p.available() > 0)
		{
			char c = p.read();
			Serial1.print(c);
		}
	}

}

