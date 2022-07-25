#include <REGX52.H>

/**
  * @brief	串口通讯初始化
  *	@param	无 
  *	@retval	无
  * @notes 	默认不开启中断
 */
void Uart_Init()  //9600bps@11.0592MHz
{
	PCON &= 0x7F;		//波特率不倍速
	SCON = 0x50; 		//等效下方按位寻址
	
//	SM0 = 0;//
//	SM1 = 1;//工作方式1，八位UART，波特率可变
//			//1位起始位，8位数据位（低位在前），1位停止位
//	REN = 1;//REN = 1时允许接收数据
//	TB8 = 0;
//	RB8 = 0;
//	TI = 0;
//	RI = 0;	
	
	//启用定时器1
	TMOD &= 0x0F;		//清除定时器1模式位
	TMOD |= 0x20;		//设置定时器模式
	
	TL1 = 0xFD;		//设定定时初值
	TH1 = 0xFD;		//设定定时器重装值

	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	EA = 1;
	ES = 1;			//串口1中断允许
	PCON = 0;
}


/**
  * @brief	串口发送单个字符
  *	@param	Data 需要发送的数据   
  *	@retval	无
  * @notes  
 */
void Uart_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0);
	TI = 0;
}

/**
  * @brief	串口发送字符串
  *	@param	*ps 带传入字符串的首地址  
  *	@retval	无
  * @notes  
 */
void Uart_SendString(unsigned char *ps)
{
	while(*ps!='\0')
	{
	Uart_SendByte(*ps);
	ps++;
	}
}

/**
  * @brief	接收中断模板   
  *	@retval	无
  * @notes  
 */
//void UART_TxRoutine() interrupt 4
//{
//	if(RI == 1)
//	{
//		RI= 0;
//	}
//}

/**
  * @brief	串口发送数据中断模板   
  *	@retval	无
  * @notes  
 */
//void UART_RxRoutine() interrupt 4
//{
//	if(TI == 1)
//	{
//		TI= 0;
//	}
//}