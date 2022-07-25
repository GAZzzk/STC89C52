#ifndef __DS1302_H__
#define __DS1302_H__
extern unsigned char g_ds1302_times[];
unsigned char ds1302_read_byte(unsigned char command);
void ds1302_write_byte(unsigned char command,unsigned char Data);
void DS1302_Init();
void ds1302_read_time();
void ds1302_set_time(void);
#endif 
