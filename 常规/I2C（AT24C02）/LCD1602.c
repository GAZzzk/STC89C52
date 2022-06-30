#include <REGX52.H>
#include "Delay.h"
sbit LCD_RS=P2^6;
sbit LCD_WR=P2^5;
sbit LCD_EN=P2^7;
#define LCD_DataPort P0

//void delayms1(unsigned int xms1)	
//	{
//		unsigned char i, j;
//		while (xms1){
//		i = 2;
//		j = 239;
//		do
//		{
//			while (--j);
//		} while (--i);
//		xms1--;
//	}	
//		
//}

/******写指令*******************************/
void LCD_WriteCommand (unsigned char Command)
{
	LCD_RS = 0;//写指令
	LCD_WR = 0;//写模式
	LCD_DataPort = Command;//写入命令
	LCD_EN = 1;
	Delayms(1);
	LCD_EN = 0;
	Delayms(1);//保证写入
}

/******写数据*******************************/
void LCD_WriteData (unsigned char Data)
{
	LCD_RS = 1;//写数据
	LCD_WR = 0;//写模式
	LCD_DataPort = Data;//写入命令
	LCD_EN = 1;
	Delayms(1);
	LCD_EN = 0;
	Delayms(1);//保证写入
}

/******初始化*******************************/
void LCD_Init(void)
{
	LCD_WriteCommand(0x38);//八位数据，两行显示，5*7点阵
	LCD_WriteCommand(0x0c);//显示开，光标关，闪烁关
	LCD_WriteCommand(0x06);//数据读写操作后，光标自动加1，画面不动
	LCD_WriteCommand(0x01);//清屏
}

/******设置光标位置*******************************/
void LCD_SetCursor(unsigned char Line,unsigned char Column)
{
		if(Line == 1)
	{
		LCD_WriteCommand(0x80 | (Column - 1));
	}
	else
	{
		LCD_WriteCommand(0x80 | (Column - 1)+0x40);
	}
}
/******显示单个字符*******************************/
void LCD_ShowChar(unsigned char Line,unsigned char Column,unsigned char Char)
{
	LCD_SetCursor(Line,Column);
	LCD_WriteData(Char);
}

/******显示字符串*******************************/
void LCD_ShowString(unsigned char Line,unsigned char Column,unsigned char  *String)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i = 0;String[i] != '\0';i++)
	{
		LCD_WriteData(String[i]);
	}
}

int LCD_Pow(int X,int Y)
{
	unsigned char i ;
	int Result = 1;
	for(i=0;i<Y;i++)
	{
		Result *= X;
	}
	return Result;
}

/******显示无符号十进制数字*******************************/
void LCD_ShowNum(unsigned char Line,unsigned char Column,unsigned int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(10,i-1)%10);
	}
}

/******显示有符号十进制数字*******************************/
void LCD_ShowSingedNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int  Number1;
	LCD_SetCursor(Line,Column);
	if(Number >=0 )
	{
		LCD_WriteData('+');
		Number1 = Number;
	}
	else
	{
		LCD_WriteData('-');
		Number1 = -Number;

	}
	for(i=Length;i>0;i--)
	{
		
	}
}

/******显示有符号十六进制数字*******************************/
void LCD_ShowHexNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	unsigned int  HexNumber;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		HexNumber = Number/LCD_Pow(16,i-1)%16;
		if(HexNumber  < 10)
		{
			LCD_WriteData('0'+HexNumber);
		}
		else 
		{
			LCD_WriteData('A'+HexNumber-10);
		}
	}
}

/******显示有符号十六进制数字*******************************/
void LCD_ShowBinNum(unsigned char Line,unsigned char Column,int Number,unsigned char Length)
{
	unsigned char i;
	LCD_SetCursor(Line,Column);
	for(i=Length;i>0;i--)
	{
		LCD_WriteData('0'+Number/LCD_Pow(2,i-1)%2);
	}
}