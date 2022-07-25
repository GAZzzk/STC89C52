#include <REGX52.H>
extern unsigned char g_time_flag;
/**
  * @brief	启用定时器0，1毫秒@11.0592MHz
  *	@param	无   
  *	@retval	无
  * @notes  
 */
 void Timer0_Init(void)		
{
//	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TMOD |= 0x01;		//设置定时器模式
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	TR0 = 1;		//定时器0开始计时
	
	ET0 = 1;		//ET0:T0的溢出中断允许位，ET0 = 1允许T0中断
	EA = 1;			//CPU总中断允许控制位，EA = 1 CPU开放中断，各中断源首先受EA控制，
					//其次还受各中断源自己的中断允许控制位标志中断
	PT0 = 0;		//定时器0中断优先控制位。
}


/**
  * @brief 定时器0中断模板
  *	@param	无 
  *	@retval	无
  * @notes  此为模板，使用时放在main.c中
 */
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;		//设置定时初值
	TH0 = 0xFC;		//设置定时初值
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		P2_0=~P2_0;
		g_time_flag=!g_time_flag;
	}
}