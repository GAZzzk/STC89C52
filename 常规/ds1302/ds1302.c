#include <REGX52.H>

sbit SCLK_1302 = P3^6;
sbit IO_1302 = P3^4;
sbit CE_1302 = P3^5;

#define DS1302_SECOND		0x80
#define DS1302_MINUTE		0x82
#define DS1302_HOUR			0x84
#define DS1302_DATE			0x86
#define DS1302_MONTH		0x88
#define DS1302_DAY			0x8A
#define DS1302_YEAR			0x8C
#define DS1302_WP			0x8E


unsigned char g_ds1302_times[]={19,11,16,12,59,55,6};
/**
  * @brief	ds1302初始化
  *	@param	NULL
  *	@retval	NULL
  * @notes  
 */
void DS1302_Init()
{
	CE_1302 = 0;
	SCLK_1302 = 0;
}

/**
  * @brief	ds1302写入一个字节
  *	@param	command 写入命令地址
  * @param	Data 写入的数据 
  *	@retval	NULL
  * @notes  
 */
void ds1302_write_byte(unsigned char command,unsigned char Data)
{
	unsigned char i=0;
	CE_1302 = 1;
	for(i = 0;i < 8; i++)
	{	
		IO_1302 = (0x01 <<i) & command;
		SCLK_1302 = 1;
		SCLK_1302 = 0;

	}
	for(i = 0;i < 8; i++)
	{	
		IO_1302 = (0x01 <<i) & Data;
		SCLK_1302 = 1;
		SCLK_1302 = 0;
	}
	CE_1302 = 0;
}

/**
  * @brief	ds1302读取一个字节
  *	@param	command 读取字节的地址
  *	@retval	Data 读取出的字节
  * @notes  
 */
unsigned char ds1302_read_byte(unsigned char command)
{
	unsigned char  i=0;
	unsigned char Data =0x00;
	command |= 0x01;

	CE_1302 = 1;
	for(i = 0;i < 8; i++)
	{	
		IO_1302 = (0x01 <<i) & command;
		SCLK_1302 = 0;
		SCLK_1302 = 1;
	}
	for(i = 0;i < 8; i++)
	{	
		SCLK_1302 = 1;
		SCLK_1302 = 0;
		if(IO_1302 == 1)
		{
			Data = Data|(0x01<<i);
		}
	}
	CE_1302 = 0;
	IO_1302 = 0;
	return Data;
}

/**
  * @brief	ds1302读取时间
  *	@param	NULL   
  *	@retval	NULL
  * @notes  
 */
void ds1302_read_time()
{

	unsigned char temp;
	temp = ds1302_read_byte(DS1302_YEAR);
	g_ds1302_times[0] = (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_MONTH);
	g_ds1302_times[1] = (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_DATE);
	g_ds1302_times[2] = (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_HOUR);
	g_ds1302_times[3] = (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_MINUTE);
	g_ds1302_times[4] = (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_SECOND);
	g_ds1302_times[5] =  (temp / 16) * 10 + temp % 16;

	temp = ds1302_read_byte(DS1302_DAY);
	g_ds1302_times[6] =  (temp / 16) * 10 + temp % 16;
} 

/**
  * @brief	ds1302设置时间
  *	@param	NULL
  *	@retval	NULL
  * @notes  
 */
void ds1302_set_time(void)
{
	ds1302_write_byte(DS1302_WP,0x00);
	ds1302_write_byte(DS1302_YEAR,(g_ds1302_times[0] / 10) * 16 + g_ds1302_times[0] % 10);
	ds1302_write_byte(DS1302_MONTH,(g_ds1302_times[0] / 10) * 16 + g_ds1302_times[1] % 10);
	ds1302_write_byte(DS1302_DATE,(g_ds1302_times[0] / 10) * 16 + g_ds1302_times[2] % 10);
	ds1302_write_byte(DS1302_HOUR,g_ds1302_times[3] / 10 * 16 + g_ds1302_times[3] % 10);
	ds1302_write_byte(DS1302_MINUTE,g_ds1302_times[4] / 10 * 16 + g_ds1302_times[4] % 10);
	ds1302_write_byte(DS1302_SECOND,g_ds1302_times[5] / 10 * 16 + g_ds1302_times[5]  % 10);
	ds1302_write_byte(DS1302_DAY,g_ds1302_times[6] / 10 * 16+ g_ds1302_times[6] % 10);
	ds1302_write_byte(DS1302_WP,0x80);
}