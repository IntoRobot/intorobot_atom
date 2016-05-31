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


void setup_wifi_test_init_01()
{  

	Serial1.begin(115200);
	Serial1.println("setup_wifi_test_init_01");
	
	Bridge.begin();
	
}

//查看WiFi连接状态
void loop_wifi_test_get_st_01()
{  

//	#define CMD "cat"
//	#define PRAM "/proc/mtd"


	static int run_flag=1;

	if(run_flag==1)
	{
		run_flag=0;
		
		Process p;		// Create a process and call it "p"

		p.runShellCommand("/usr/bin/pretty-wifi-info.lua");

		while (p.available() > 0)
		{
			char c = p.read();
			Serial1.print(c);
		}
	}

}

//创建脚本并运行
void setup_wifi_test_mdf_01()
{  

	Serial1.begin(115200);
	Serial1.println("setup_wifi_test_mdf_01================");
	
	Bridge.begin();
	
}

void loop_wifi_test_mdf_02()
{
	static int run_flag=1;
	
	if(run_flag==1)
	{
		run_flag=0;
		
		//创建脚本
		FileSystem.begin();
		File script = FileSystem.open("/tmp/wlan-stats.sh", FILE_WRITE);
		script.print("iwconfig | grep apcli0");
		//script.print("ls");
		script.close();  // close the file

		//修改权限
		Process chmod;
		chmod.begin("chmod");      // chmod: change mode
		chmod.addParameter("777");  // x stays for executable
		chmod.addParameter("/tmp/wlan-stats.sh");  // path to the file to make it executable
		chmod.run();

		//执行脚本
		/*	执行脚本runShellCommand 执行命令begin
		Process myscript;
		myscript.begin("/tmp/wlan-stats.sh");
		myscript.run();*/

		Process myscript;
		myscript.runShellCommand("/tmp/wlan-stats.sh");
		
		//获取运行结果

		while (myscript.available() > 0)
		{
			char c = myscript.read();
			Serial1.print(c);
		}

		/*
		
		String output = "";
		while (myscript.available()) 
		{
		output += (char)myscript.read();
		}
		// remove the blank spaces at the beginning and the ending of the string
		output.trim();	//整理数据
		
		Serial1.println(output);
		Serial1.flush();		//等待发送完毕
		*/
	}
}

void printMAC(byte mac[6]) {
  // the MAC address of your Wifi shield
  // print your MAC address
  SerialUSB.print(mac[5], HEX);
  SerialUSB.print(":");
  SerialUSB.print(mac[4], HEX);
  SerialUSB.print(":");
  SerialUSB.print(mac[3], HEX);
  SerialUSB.print(":");
  SerialUSB.print(mac[2], HEX);
  SerialUSB.print(":");
  SerialUSB.print(mac[1], HEX);
  SerialUSB.print(":");
  SerialUSB.print(mac[0], HEX);
}

void printEncryptionType(int thisType) {
  // read the encryption type and print out the name:
  switch (thisType) {
    case ENC_TYPE_WEP:
      SerialUSB.println("WEP");
      break;
    case ENC_TYPE_WAP:
      SerialUSB.println("WPA");
      break;
    case ENC_TYPE_WAP2:
      SerialUSB.println("WPA2");
      break;
    case ENC_TYPE_NONE:
      SerialUSB.println("None");
      break;
    case ENC_TYPE_ERRER:
      SerialUSB.println("EERER");
      break;
  }
}

void listNetworks() {
    byte mac[6];
  // scan for nearby networks:
  SerialUSB.println("** Scan Networks **");
  int numSsid = WiFi.scanNetworks();
  if (numSsid == -1)
  {
    SerialUSB.println("Couldn't get a wifi connection");
    while (true);
  }

  // print the list of networks seen:
  SerialUSB.print("number of available networks:");
  SerialUSB.println(numSsid);

  // print the network number and name for each network found:
  for (int thisNet = 0; thisNet < numSsid; thisNet++) {
    SerialUSB.print(thisNet);
    SerialUSB.print(") ");
    SerialUSB.print(WiFi.SSID(thisNet));
    SerialUSB.print("\tMAC: ");
    WiFi.BSSID(thisNet,mac);
    printMAC(mac);
    SerialUSB.print("\tSignal: ");
    SerialUSB.print(WiFi.RSSI(thisNet));
    SerialUSB.print("%");
    SerialUSB.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType(thisNet));
  }
}

void CurrentNetworks() {
    byte mac[6];
    // scan for nearby networks:
    SerialUSB.println("** Current Networks **");
    SerialUSB.print("SSID: ");
    SerialUSB.print(WiFi.SSID());
    SerialUSB.print("\tMAC: ");
    WiFi.BSSID(mac);
    printMAC(mac);
    SerialUSB.print("\tSignal: ");
    SerialUSB.print(WiFi.RSSI());
    SerialUSB.print("%");
    SerialUSB.print("\tEncryption: ");
    printEncryptionType(WiFi.encryptionType());
}

void CurrentIfConfig() {
    byte mac[6];
    // scan for nearby networks:
    SerialUSB.println("** Current If config**");
    
    SerialUSB.print("MAC: ");
    WiFi.macAddress(mac);
    printMAC(mac);

    SerialUSB.print("LocalIp: ");
    IPAddress ip = WiFi.localIP();
    SerialUSB.println(ip);

    SerialUSB.print("SubnetMask: ");
    ip = WiFi.subnetMask();
    SerialUSB.println(ip);

    SerialUSB.print("GateWayIp: ");
    ip = WiFi.gatewayIP();
    SerialUSB.println(ip);

}

//创建脚本并运行
void setup_wifi_test()
{  
    SerialUSB.begin(115200);
    
    // Bridge startup
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);
    Bridge.begin();
    digitalWrite(13, HIGH);
}

void loop_wifi_test()
{
    // scan for existing networks:
    SerialUSB.println("Scanning available networks...");

    //listNetworks();
    //CurrentNetworks();
    //CurrentIfConfig();
    //delay(10000);
    
    /*SerialUSB.print("wifi connent status:");
    SerialUSB.println(WiFi.status());


    SerialUSB.println("setCredentials molmc-jiluyou   ");
    WiFi.setCredentials("molmc-jiluyou", "");
    delay(10000);

    SerialUSB.println("setCredentials molmc-netgear   26554422");
    WiFi.setCredentials("molmc-netgear", "26554422");
    delay(10000);

    SerialUSB.println("setCredentials molmc-ji  123456 ");
    WiFi.setCredentials("molmc-ji", "123456");
    delay(10000);

    SerialUSB.println("setCredentials molmc-netgear   26554422");
    WiFi.setCredentials("molmc-netgear", "26554422");
    delay(10000);*/
    
    /*SerialUSB.println("setCredentials molmc-netgear   26554422");
    WiFi.setCredentials("molmc-netgear", "26554422");

    SerialUSB.print("wifi connent:");

    WiFi.connect();
    delay(8000);
    int i=10;
    while(i)
    {
        SerialUSB.print("wifi connent status:");
        SerialUSB.println(WiFi.status());
        delay(1000);
        i--;
    }
    
    SerialUSB.println("wifi connent config: WiFi.config(local_ip)");
	WiFi.config("192.168.1.89");
    delay(10000);
    SerialUSB.println("wifi connent config: WiFi.config(local_ip, dns_server");
	WiFi.config("192.168.1.89", "8.8.8.8");
    delay(10000);
    SerialUSB.println("wifi connent config: WiFi.config(local_ip, dns_server, gateway)");
    WiFi.config("192.168.1.89", "8.8.8.8", "192.168.1.89");
    delay(10000);
    SerialUSB.println("wifi connent config: WiFi.config(local_ip, dns_server, gateway, subnet)");
    WiFi.config("192.168.1.89", "8.8.8.8", "192.168.1.89", "192.168.1.89");
    delay(10000);

    
    IPAddress local_ip(192,168,1,45);
    IPAddress dns_server(192,168,1,1);
    IPAddress gateway(192,168,1,255);
    IPAddress subnet(255,255,255,0);
    
    SerialUSB.println("wifi connent config: IPAddress  WiFi.config(local_ip)");
	WiFi.config(local_ip);
    delay(10000);
    SerialUSB.println("wifi connent config: IPAddress  WiFi.config(local_ip, dns_server)");
	WiFi.config(local_ip, dns_server);
    delay(10000);
    SerialUSB.println("wifi connent config: IPAddress  WiFi.config(local_ip, dns_server, gateway)");
    WiFi.config(local_ip, dns_server, gateway);
    delay(10000);
    SerialUSB.println("wifi connent config: IPAddress  WiFi.config(local_ip, dns_server, gateway, subnet)");
    WiFi.config(local_ip, dns_server, gateway, subnet);
    delay(10000);

    SerialUSB.println("wifi connent config: setDNS(const char *dns_server1)");
    WiFi.setDNS("192.168.1.89");
    delay(10000);
    SerialUSB.println("wifi connent config: setDNS(const char *dns_server1,const char *dns_server2)");
    WiFi.setDNS("192.168.1.89", "192.168.1.90");
    delay(10000);
        
    IPAddress dns_server1(8,8,8,8);
    IPAddress dns_server2(8,8,8,9);

    SerialUSB.println("wifi connent config: IPAddress setDNS(const char *dns_server1)");
    WiFi.setDNS(dns_server1);
    delay(10000);
    SerialUSB.println("wifi connent config: IPAddress setDNS(const char *dns_server1,const char *dns_server2)");
    WiFi.setDNS(dns_server1, dns_server2);
    delay(10000);
    */

    SerialUSB.println("wifi connent config: hostByName");
    IPAddress aResult;
    WiFi.hostByName("www.baidu.com", aResult);
    SerialUSB.println(aResult);
    
    SerialUSB.println("wifi connent config: ping");
    IPAddress remoteIP(58,217,200,37);
	SerialUSB.println(WiFi.ping(remoteIP));
	SerialUSB.println(WiFi.ping(remoteIP, 2));
	SerialUSB.println(WiFi.ping("www.baidu.com"));
	SerialUSB.println(WiFi.ping("www.baidu.com", 3));




    while(1);


    SerialUSB.print("wifi connent status:");
    SerialUSB.println(WiFi.status());
}

