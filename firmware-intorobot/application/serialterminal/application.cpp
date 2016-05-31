/**
 *******************************************************************************
 * @file    : serialterminal
 * @author  : robin
 * @version : V1.0.0
 * @date    : 30-November-2014
 * @brief   :  USB-to-Serial    
 Allows you to use the stm32 as a serial terminal for the Linux side on the IntoRobot Atom.
 Upload this to an Atom via serial (not WiFi) then open
 the serial monitor at 115200 to see the boot process of Linux.
 You can also use the serial monitor as a basic command line
 interface for Linux using this sketch.

 From the serial monitor the following commands can be issued:

 '~' followed by '0' -> Set the UART speed to 57600 baud
 '~' followed by '1' -> Set the UART speed to 115200 baud
 '~' followed by '2' -> Set the UART speed to 250000 baud
 '~' followed by '3' -> Set the UART speed to 500000 baud
 '~' followeb by '~' -> Sends the bridge's shutdown command to
                        obtain the console.
 *******************************************************************************
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
#include "application.h"
long linuxBaud = 115200;

void setup() {
  SerialUSB.begin(115200);      // open serial connection via USB-Serial
  SerialBridge.begin(linuxBaud);  // open serial connection to Linux
}

boolean commandMode = false;

void loop() {
  // copy from USB-CDC to UART
  int c = SerialUSB.read();              // read from USB-CDC
  if (c != -1) {                      // got anything?
    if (commandMode == false) {       // if we aren't in command mode...
      if (c == '~') {                 //    Tilde '~' key pressed?
        commandMode = true;           //       enter in command mode
      } else {
        SerialBridge.write(c);             //    otherwise write char to UART
      }
    } else {                          // if we are in command mode...
      if (c == '0') {                 //     '0' key pressed?
        SerialBridge.begin(57600);         //        set speed to 57600
        SerialUSB.println("Speed set to 57600");
      } else if (c == '1') {          //     '1' key pressed?
        SerialBridge.begin(115200);        //        set speed to 115200
        SerialUSB.println("Speed set to 115200");
      } else if (c == '2') {          //     '2' key pressed?
        SerialBridge.begin(250000);        //        set speed to 250000
        SerialUSB.println("Speed set to 250000");
      } else if (c == '3') {          //     '3' key pressed?
        SerialBridge.begin(500000);        //        set speed to 500000
        SerialUSB.println("Speed set to 500000");
      } else if (c == '~') {          //     '~` key pressed?
                                      //        send "bridge shutdown" command
        SerialBridge.write((uint8_t *)"\xff\0\0\x05XXXXX\x7f\xf9", 11);
        SerialUSB.println("Sending bridge's shutdown command");
      } else {                        //     any other key pressed?
        SerialBridge.write('~');           //        write '~' to UART
        SerialBridge.write(c);             //        write char to UART
      }
      commandMode = false;            //     in all cases exit from command mode
    }
  }

  // copy from UART to USB-CDC
  c = SerialBridge.read();                 // read from UART
  if (c != -1) {                      // got anything?
    SerialUSB.write(c);                  //    write to USB-CDC
  }
}

