#include "REGX51.H"

sbit I2C_SCL = P2^1;
sbit I2C_SDA = P2^0;

/**
  * @brief	I2C��ʼ
  *	@param	��   
  *	@retval	��
  * @notes  I2CΪ�����������˽�������1ʵ�����ǹض�mos�ܣ������������������ߵ�ƽ
  *         ��0ʱ��Ӧ��mos�ܵ�ͨ�����������
 */
void I2C_Start(void)
{
	I2C_SDA = 1;
    I2C_SCL = 1;//�ڿ�ʼ֮ǰ��ȷ��SDA��SCLΪ�ߵ�ƽ״̬��������״̬

    I2C_SDA = 0;//��SCL�ߵ�ƽ�ڼ䣬SDA�ɸߵ�ƽ��0��ʾI2C��ʼ�ź�
    I2C_SCL = 0;//��SCL���ף���������������ݴ���
}

/**
  * @brief	I2Cֹͣ
  *	@param	�� 
  *	@retval	��
  * @notes  
 */
void I2C_Stop(void)
{
    I2C_SDA = 0;//��֤SDAΪ0
    I2C_SCL = 1;
    I2C_SDA = 1;//SCL�ߵ�ƽ�ڼ䣬��SDA��0��1ΪI2Cֹͣ�źţ��ҽ����� 
                //SDA��SCL��Ϊ�ߵ�ƽ����ʾΪ����״̬
}


/**
  * @brief	I2C����һ���ֽ�
  *	@param	Byte Ҫ���͵��ֽ� 
  *	@retval	��
  * @notes  
 */
void I2C_SendByte(unsigned char Byte)
{
    unsigned char i = 0;
    for (i=0;i<8;i++)         //ѭ��8�Σ�����8λ����
    {
        I2C_SDA = Byte&(0x80>>i); //I2C���ݴ����ɸ�λ��ʼ��0x80��Ӧ1000 0000
                                  //����֮��ֻ�������λ������iλ
                                  //�Դ˷����Ӹߵ���ȡ��ÿһλ
        I2C_SCL = 1;
        I2C_SCL = 0;
    }
}



/**
  * @brief	I2C����һ���ֽ�
  *	@param	��  
  *	@retval	Byte ���ؽ��յ��ֽ�
  * @notes  
 */
unsigned char I2C_ReceiveByte(void)
{
    unsigned char i ,Byte = 0x00;
	I2C_SDA = 1;				//��SDA����Ȩ���ڴӻ�
    for(i=0;i<8;i++)            //ѭ��8�Σ���ȡ��λ����
    {            
        I2C_SCL = 1;
		if (I2C_SDA)            //���SDA�����Ǹߵ�ƽ
        { 
            Byte |= (0x80>>i);  //0x80��Ӧ1000 0000��
                                // |= �����ݴ���Byte��
        }
		I2C_SCL = 0;
    }
    return Byte;
}


/**
  * @brief	I2C����Ӧ��
  *	@param	AckBit Ӧ��λ 0ΪӦ��1Ϊ��Ӧ��
  *	@retval	��
  * @notes  
 */
void I2C_SendAck(unsigned char AckBit)
{
    I2C_SDA = AckBit; 
    I2C_SCL = 1;
    I2C_SCL = 0;
}


/**
  * @brief	I2C����Ӧ��
  *	@param	��
  *	@retval	Ackbit ����Ӧ��λ
  * @notes  
 */
unsigned char I2C_ReceiveAck(void)
{
    unsigned char Ackbit;
    I2C_SDA = 1;        
    I2C_SCL = 1;       //�Ƚ�SDA��SCL�ͷ� 
    Ackbit = I2C_SDA;  //��SCL�ߵ�ƽ�ڼ�,SDAΪ0���ʾ���յ��˴ӻ�Ӧ��
    I2C_SCL = 0;
    return Ackbit;     
}
