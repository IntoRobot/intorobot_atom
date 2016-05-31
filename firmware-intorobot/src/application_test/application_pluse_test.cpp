/**
 ******************************************************************************
 * @file     : application.cpp
 * @author   : robin
 * @version  : V1.0.0
 * @date     : 6-December-2014
 * @brief    :   
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
 */


#include "../application.h"


uint8_t pluse0 = TIMER2_CH1;
int32_t pluseWidth;
int pluseInput = D0;




void setup_pluseIn_test(void)
{  
    // Initialize D0 + D7 pin as output  
    // It's important you do this here, inside the setup() function rather than outside it or in the loop function.  
	SerialBridge.begin(115200);

	pinMode(pluse0, OUTPUT);
	analogWrite(pluse0,153); // 60%
	pinMode(pluseInput, INPUT);
	
}

void loop_pluseIn_test(void)
{  
	pluseWidth = pulseIn(pluseInput,0,2000000);
	SerialBridge.print(pluseWidth);
	SerialBridge.print("\r\n");

}




