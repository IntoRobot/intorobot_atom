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

uint8_t pwmChannel1 = TIMER2_CH1;
uint8_t pwmChannel2 = TIMER2_CH2;
uint8_t pwmChannel3 = TIMER2_CH3;
uint8_t pwmChannel4 = TIMER2_CH4;

void setup_pwm_test(void)
{
	pinMode(pwmChannel1,OUTPUT);
	pinMode(pwmChannel2,OUTPUT);
	pinMode(pwmChannel3,OUTPUT);
	pinMode(pwmChannel4,OUTPUT);

	analogWrite(pwmChannel1,20); // 占空比值 0 - 255 频率500Hz
	analogWrite(pwmChannel2,100);
	analogWrite(pwmChannel3,150);
	analogWrite(pwmChannel4,200);
	
}

void loop_pwm_test(void)
{
	;
}


