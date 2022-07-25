#include <REGX52.H>

/**
  * @brief	����ͨѶ��ʼ��
  *	@param	�� 
  *	@retval	��
  * @notes 	Ĭ�ϲ������ж�
 */
void Uart_Init()  //9600bps@11.0592MHz
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON = 0x50; 		//��Ч�·���λѰַ
	
//	SM0 = 0;//
//	SM1 = 1;//������ʽ1����λUART�������ʿɱ�
//			//1λ��ʼλ��8λ����λ����λ��ǰ����1λֹͣλ
//	REN = 1;//REN = 1ʱ�����������
//	TB8 = 0;
//	RB8 = 0;
//	TI = 0;
//	RI = 0;	
	
	//���ö�ʱ��1
	TMOD &= 0x0F;		//�����ʱ��1ģʽλ
	TMOD |= 0x20;		//���ö�ʱ��ģʽ
	
	TL1 = 0xFD;		//�趨��ʱ��ֵ
	TH1 = 0xFD;		//�趨��ʱ����װֵ

	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	EA = 1;
	ES = 1;			//����1�ж�����
	PCON = 0;
}


/**
  * @brief	���ڷ��͵����ַ�
  *	@param	Data ��Ҫ���͵�����   
  *	@retval	��
  * @notes  
 */
void Uart_SendByte(unsigned char Byte)
{
	SBUF = Byte;
	while(TI == 0);
	TI = 0;
}

/**
  * @brief	���ڷ����ַ���
  *	@param	*ps �������ַ������׵�ַ  
  *	@retval	��
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
  * @brief	�����ж�ģ��   
  *	@retval	��
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
  * @brief	���ڷ��������ж�ģ��   
  *	@retval	��
  * @notes  
 */
//void UART_RxRoutine() interrupt 4
//{
//	if(TI == 1)
//	{
//		TI= 0;
//	}
//}