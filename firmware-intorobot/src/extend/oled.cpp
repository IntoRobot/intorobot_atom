

#include "oled.h"

OLED::OLED(u16 pinDC,u16 pinRST,u16 pinSDA,u16 pinSCL)
{
    DC =  pinDC;
    RST = pinRST;
    SDA = pinSDA;
    SCL = pinSCL;
}

void OLED::begin(void)
{
    pinMode(RST,OUTPUT);  // 初始化IO
    pinMode(DC,OUTPUT);
    pinMode(SDA,OUTPUT);
    pinMode(SCL,OUTPUT);

    delay(100);

    digitalWrite(RST,0);
    delay(200);
    digitalWrite(RST,1);

    OLED_Init(); // 初始化LED
}

void OLED::OLED_WrDat(unsigned char dat)//写数据
{
	unsigned char i;
    
	digitalWrite(DC,1);
    
   
    for(i=0;i<8;i++)
	{
		if((dat << i) & 0x80)
		{
			digitalWrite(SDA,1);
		}
		else
		{
            digitalWrite(SDA,0);
		}
        
		digitalWrite(SCL,0);
		digitalWrite(SCL,1);
	}
}



void OLED::OLED_WrCmd(unsigned char cmd)//写命令
{
	unsigned char i;
    
	digitalWrite(DC,0);
    
    
    for(i=0;i<8;i++)
	{
		if((cmd << i) & 0x80)
		{
			digitalWrite(SDA,1);
		}
		else
		{
            digitalWrite(SDA,0);
		}
        
		digitalWrite(SCL,0);
		digitalWrite(SCL,1);
	}
}


void OLED::OLED_SetPos(unsigned char x, unsigned char y)//设置起始点坐标
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x & 0xf0) >> 4)|0x10);
	OLED_WrCmd((x & 0x0f)|0x01);
}

void OLED::OLED_Fill(unsigned char bmp_dat)//全屏填充
{
	unsigned char y,x;
    
	for(y = 0; y < 8; y++)
	{
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
        
		for(x = 0; x < X_WIDTH; x++)
		{
			OLED_WrDat(bmp_dat);
		}
	}
}

void OLED::OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}

void OLED::OLED_Init(void)
{
	OLED_WrCmd(0xae);
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa1);//--Set SEG/Column Mapping     0xa0,0xa1
	OLED_WrCmd(0xc8);//Set COM/Row Scan Direction   0xc0,0xc8
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00);
	OLED_SetPos(0,0);
    
}

void OLED::OLED_6x8Str(unsigned char x, unsigned char y, char *ch)
{
	unsigned char c = 0,i = 0,j = 0;
    
	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
        
		if(x > 126)
		{
			x = 0;
            y++;
		}
        
		OLED_SetPos(x,y);
        
		for(i = 0; i < 6; i++)
		{
			OLED_WrDat(F6x8[c][i]);
		}
        
		x += 6;
		j++;
	}
}

void OLED::OLED_8x16Str(unsigned char x, unsigned char y, char *ch)
{
	unsigned char c = 0,i = 0,j = 0;
    
	while (ch[j] != '\0')
	{
		c = ch[j] - 32;
        
		if(x > 120)
		{
			x = 0;
            //y++;
            y = y+2;
		}
        
		OLED_SetPos(x,y);
        
		for(i = 0; i < 8; i++)
		{
			OLED_WrDat(F8X16[c*16+i]);
		}
        
		OLED_SetPos(x,y+1);
        
		for(i=0;i<8;i++)
		{
			OLED_WrDat(F8X16[c*16+i+8]);
		}
        
		x += 8;
		j++;
	}
}






