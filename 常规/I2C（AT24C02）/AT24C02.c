#include <REGX51.H>
#include "I2C.h"
#define AT2402_ADDRESS 0xa0  //0xa0对应1010 000 0，最后一位置0，为写模式

/**
  * @brief	AT24C02写一字节数据
  *	@param	WordAddress 写入字节的地址
  * @param	Data 写入的数据   
  *	@retval	无
  * @notes  
 */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
    I2C_Start();                   //I2C开始
    I2C_SendByte(AT2402_ADDRESS);  //找到ATAT24C02的器件地址
    I2C_ReceiveAck();              //接收AT24C02应答  
    I2C_SendByte(WordAddress);     //写入数据的地址
    I2C_ReceiveAck();              //接收AT24C02应答    
    I2C_SendByte(Data);            //写入数据
    I2C_ReceiveAck();              //接收AT24C02应答    
    I2C_Stop();                    //I2C停止
}

/**
  * @brief	AT24C02读取一字节数据
  *	@param	WordAddress	 读取字节的8位地址 
  *	@retval	Data 读取的字节
  * @notes  
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    unsigned char Data;
    I2C_Start();					//I2C开始
    I2C_SendByte(AT2402_ADDRESS);	//找到ATAT24C02的器件地址
    I2C_ReceiveAck();				//接收AT24C02应答  
    I2C_SendByte(WordAddress);		//写入数据的地址
    I2C_ReceiveAck();				//接收AT24C02应答
    I2C_Start();               		//I2C开始        
    I2C_SendByte(AT2402_ADDRESS | 0x01);//7位器件地址，第八位置1，表示读模式
    I2C_ReceiveAck();				//接收AT24C02应答 	
    Data = I2C_ReceiveByte();			//读取AT24C02的数据
    I2C_SendAck(1);                 //不发送应答，发送与不发生都可以
    I2C_Stop();						//I2C停止
    return Data;
}