

#ifndef OLED_H_
#define OLED_H_

#include "application.h"
#include "oled_codetab.h"


/**
SCK --- 
SDA --- 
RST ---   // 直接IO控制
DC  ---  数据命令选择 1 表示发送数据 0表示发送命令
**/



#define XLevelL				0x00
#define XLevelH				0x10
#define XLevel	    		((XLevelH&0x0F)*16+XLevelL)
#define Max_Column			128
#define Max_Row				64
#define	Brightness			0xCF 
#define X_WIDTH 			128
#define Y_WIDTH 			64

// 0.96 OLED 屏幕 SPI模拟传输

class OLED
{

	public:
	OLED(u16 pinDC,u16 pinRST,u16 pinSDA,u16 pinSCL);
	//OLED控制用函数
	void begin(void);
	void OLED_WrDat(unsigned char dat);//写数据
	void OLED_WrCmd(unsigned char cmd);//写命令
	void OLED_SetPos(unsigned char x, unsigned char y);//设置起始点坐标
	void OLED_Fill(unsigned char bmp_dat);//全屏填充
	void OLED_CLS(void);//清屏
	void OLED_Init(void);//初始化
	void OLED_6x8Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);
	void OLED_8x16Str(unsigned char x, unsigned char y, char *ch);//unsigned char ch[]);


	private:
	u16 DC;
	u16 RST;
	u16 SDA;
	u16 SCL;
};


#endif 

