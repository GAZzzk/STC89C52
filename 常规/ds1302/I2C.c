#include "REGX51.H"

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
  * @brief	I2C开始
  *	@param	无   
  *	@retval	无
  * @notes  I2C为推挽输出，因此将引脚置1实际上是关断mos管，由上拉电阻拉高至高电平
  *         置0时对应，mos管导通，将输出拉底
 */
void I2C_Start(void)
{
	I2C_SDA = 1;
    I2C_SCL = 1;//在开始之前，确保SDA、SCL为高电平状态，即空闲状态

    I2C_SDA = 0;//在SCL高电平期间，SDA由高电平置0表示I2C起始信号
    I2C_SCL = 0;//将SCL拉底，方便接下来的数据传输
}

/**
  * @brief	I2C停止
  *	@param	无 
  *	@retval	无
  * @notes  
 */
void I2C_Stop(void)
{
    I2C_SDA = 0;//保证SDA为0
    I2C_SCL = 1;
    I2C_SDA = 1;//SCL高电平期间，将SDA从0置1为I2C停止信号，且结束后， 
                //SDA、SCL均为高电平，表示为空闲状态
}


/**
  * @brief	I2C发送一个字节
  *	@param	Byte 要发送的字节 
  *	@retval	无
  * @notes  
 */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i = 0;
    for (i=0;i<8;i++)         //循环8次，发送8位数据
    {
        I2C_SDA = Byte&(0x80>>i); //I2C数据传输由高位开始，0x80对应1000 0000
                                  //相与之后只保留最高位，右移i位
                                  //以此方法从高到低取出每一位
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}



/**
  * @brief	I2C接收一个字节
  *	@param	无  
  *	@retval	Byte 返回接收的字节
  * @notes  
 */
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i ,Byte = 0x00;
	I2C_SDA = 1;				//将SDA控制权交于从机
    for(i=0;i<8;i++)            //循环8次，读取八位数据
    {            
        I2C_SCL = 1;
		if (I2C_SDA)            //如果SDA线上是高电平
        { 
            Byte |= (0x80>>i);  //0x80对应1000 0000，
                                // |= 将数据存入Byte中
        }
		I2C_SCL = 0;
    }
    return Byte;
}


/**
  * @brief	I2C发送应答
  *	@param	AckBit 应答位 0为应答，1为不应达
  *	@retval	无
  * @notes  
 */
void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA = AckBit; 
    I2C_SCL = 1;
    I2C_SCL = 0;
}


/**
  * @brief	I2C接收应答
  *	@param	无
  *	@retval	Ackbit 接收应答位
  * @notes  
 */
unsigned char I2C_ReceiveAck(void)
{
    unsigned char Ackbit;
    I2C_SDA = 1;        
    I2C_SCL = 1;       //先将SDA，SCL释放 
    Ackbit = I2C_SDA;  //在SCL高电平期间,SDA为0则表示接收到了从机应答
    I2C_SCL = 0;
    return Ackbit;     
}
