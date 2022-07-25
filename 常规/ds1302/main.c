#include <REGX52.H>
#include "LCD1602.h"
#include "ds1302.h"
#include "Delay.h"
#include "Key.h"
#include "Timer.h"

unsigned char g_key;
unsigned char g_mode = 0;
unsigned char g_time_select = 0;
unsigned char g_time_flag = 0;
void time_show()
{
	ds1302_read_time();
	LCD_ShowNum(1,1,g_ds1302_times[0],2);
	LCD_ShowNum(1,4,g_ds1302_times[1],2);
	LCD_ShowNum(1,7,g_ds1302_times[2],2);
	LCD_ShowNum(2,1,g_ds1302_times[3],2);
	LCD_ShowNum(2,4,g_ds1302_times[4],2);
	LCD_ShowNum(2,7,g_ds1302_times[5],2);
}
void time_set()
{
	if(g_key == 2)
	{
		g_time_select ++;  
		g_time_select %= 6;
	}
	if(g_key == 3)
	{
		g_ds1302_times[g_time_select]++;
		if(g_ds1302_times[0]>99){g_ds1302_times[0]=0;}//年越界判断
		if(g_ds1302_times[1]>12){g_ds1302_times[1]=1;}//月越界判断
		if( g_ds1302_times[1]==1 || g_ds1302_times[1]==3 || g_ds1302_times[1]==5 || g_ds1302_times[1]==7 || 
		g_ds1302_times[1]==8 || g_ds1302_times[1]==10 || g_ds1302_times[1]==12)//日越界判断
		{
		if(g_ds1302_times[2]>31){g_ds1302_times[2]=1;}//大月
		}
		else if(g_ds1302_times[1]==4 || g_ds1302_times[1]==6 || g_ds1302_times[1]==9 || g_ds1302_times[1]==11)
		{
			if(g_ds1302_times[2]>30){g_ds1302_times[2]=1;}//小月
		}
		else if(g_ds1302_times[1]==2)
		{
			if(g_ds1302_times[0]%4==0)
			{
				if(g_ds1302_times[2]>29){g_ds1302_times[2]=1;}//闰年2月
			}
			else
			{
				if(g_ds1302_times[2]>28){g_ds1302_times[2]=1;}//平年2月
			}
		}
		if(g_ds1302_times[3]>23){g_ds1302_times[3]=0;}//时越界判断
		if(g_ds1302_times[4]>59){g_ds1302_times[4]=0;}//分越界判断
		if(g_ds1302_times[5]>59){g_ds1302_times[5]=0;}//秒越界判断
	}
    if(g_key == 4)
	{
		g_ds1302_times[g_time_select]--;
		if(g_ds1302_times[0]>99){g_ds1302_times[0]=0;}//年越界判断
		if(g_ds1302_times[1]>12){g_ds1302_times[1]=1;}//月越界判断
		if( g_ds1302_times[1]==1 || g_ds1302_times[1]==3 || g_ds1302_times[1]==5 || g_ds1302_times[1]==7 || 
		g_ds1302_times[1]==8 || g_ds1302_times[1]==10 || g_ds1302_times[1]==12)//日越界判断
		{
		if(g_ds1302_times[2]>31){g_ds1302_times[2]=1;}//大月
		}
		else if(g_ds1302_times[1]==4 || g_ds1302_times[1]==6 || g_ds1302_times[1]==9 || g_ds1302_times[1]==11)
		{
			if(g_ds1302_times[2]>30){g_ds1302_times[2]=1;}//小月
		}
		else if(g_ds1302_times[1]==2)
		{
			if(g_ds1302_times[0]%4==0)
			{
				if(g_ds1302_times[2]>29){g_ds1302_times[2]=1;}//闰年2月
			}
			else
			{
				if(g_ds1302_times[2]>28){g_ds1302_times[2]=1;}//平年2月
			}
		}
		if(g_ds1302_times[3]>23){g_ds1302_times[3]=0;}//时越界判断
		if(g_ds1302_times[4]>59){g_ds1302_times[4]=0;}//分越界判断
		if(g_ds1302_times[5]>59){g_ds1302_times[5]=0;}//秒越界判断
	}
	if(g_time_select==0 && g_time_flag==1){LCD_ShowString(1,1,"  ");}
	else {LCD_ShowNum(1,1,g_ds1302_times[0],2);}
	if(g_time_select==1 && g_time_flag==1){LCD_ShowString(1,4,"  ");}
	else {LCD_ShowNum(1,4,g_ds1302_times[1],2);}
	if(g_time_select==2 && g_time_flag==1){LCD_ShowString(1,7,"  ");}
	else {LCD_ShowNum(1,7,g_ds1302_times[2],2);}
	if(g_time_select==3 && g_time_flag==1){LCD_ShowString(2,1,"  ");}
	else {LCD_ShowNum(2,1,g_ds1302_times[3],2);}
	if(g_time_select==4 && g_time_flag==1){LCD_ShowString(2,4,"  ");}
	else {LCD_ShowNum(2,4,g_ds1302_times[4],2);}
	if(g_time_select==5 && g_time_flag==1){LCD_ShowString(2,7,"  ");}
	else {LCD_ShowNum(2,7,g_ds1302_times[5],2);}
}
void main()
{	
	Timer0_Init();
	LCD_Init();
	DS1302_Init();
	ds1302_set_time();
	LCD_ShowString(1,1,"  -  -  ");
	LCD_ShowString(2,1,"  :  :  ");
	while(1)
	{
		g_key = Key_Scan();
		if(g_key == 1)
		{
			if(g_mode==0){g_mode=1;g_time_select=0;}//功能切换
			else if(g_mode==1){g_mode=0;ds1302_set_time();}
		}
		switch(g_mode)
		{
			case 0 :time_show(); break;
			case 1 :time_set(); break;
		}

	} 
}