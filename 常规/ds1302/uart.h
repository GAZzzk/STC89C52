#ifndef __HART_H__
#define __HART_H__
void Uart_Init();
void Uart_SendByte(unsigned char Byte);
void Uart_SendString(unsigned char *ps);
#endif 
