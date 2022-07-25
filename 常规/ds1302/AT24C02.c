#include <REGX51.H>
#include "I2C.h"
#define AT2402_ADDRESS 0xa0  //0xa0��Ӧ1010 000 0�����һλ��0��Ϊдģʽ

/**
  * @brief	AT24C02дһ�ֽ�����
  *	@param	WordAddress д���ֽڵĵ�ַ
  * @param	Data д�������   
  *	@retval	��
  * @notes  
 */
void AT24C02_WriteByte(unsigned char WordAddress, unsigned char Data)
{
    I2C_Start();                   //I2C��ʼ
    I2C_SendByte(AT2402_ADDRESS);  //�ҵ�ATAT24C02��������ַ
    I2C_ReceiveAck();              //����AT24C02Ӧ��  
    I2C_SendByte(WordAddress);     //д�����ݵĵ�ַ
    I2C_ReceiveAck();              //����AT24C02Ӧ��    
    I2C_SendByte(Data);            //д������
    I2C_ReceiveAck();              //����AT24C02Ӧ��    
    I2C_Stop();                    //I2Cֹͣ
}

/**
  * @brief	AT24C02��ȡһ�ֽ�����
  *	@param	WordAddress	 ��ȡ�ֽڵ�8λ��ַ 
  *	@retval	Data ��ȡ���ֽ�
  * @notes  
 */
unsigned char AT24C02_ReadByte(unsigned char WordAddress)
{
    unsigned char Data;
    I2C_Start();					//I2C��ʼ
    I2C_SendByte(AT2402_ADDRESS);	//�ҵ�ATAT24C02��������ַ
    I2C_ReceiveAck();				//����AT24C02Ӧ��  
    I2C_SendByte(WordAddress);		//д�����ݵĵ�ַ
    I2C_ReceiveAck();				//����AT24C02Ӧ��
    I2C_Start();               		//I2C��ʼ        
    I2C_SendByte(AT2402_ADDRESS | 0x01);//7λ������ַ���ڰ�λ��1����ʾ��ģʽ
    I2C_ReceiveAck();				//����AT24C02Ӧ�� 	
    Data = I2C_ReceiveByte();			//��ȡAT24C02������
    I2C_SendAck(1);                 //������Ӧ�𣬷����벻����������
    I2C_Stop();						//I2Cֹͣ
    return Data;
}