#include <REGX52.H>
extern unsigned char g_time_flag;
/**
  * @brief	���ö�ʱ��0��1����@11.0592MHz
  *	@param	��   
  *	@retval	��
  * @notes  
 */
 void Timer0_Init(void)		
{
//	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TMOD |= 0x01;		//���ö�ʱ��ģʽ
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	TR0 = 1;		//��ʱ��0��ʼ��ʱ
	
	ET0 = 1;		//ET0:T0������ж�����λ��ET0 = 1����T0�ж�
	EA = 1;			//CPU���ж��������λ��EA = 1 CPU�����жϣ����ж�Դ������EA���ƣ�
					//��λ��ܸ��ж�Դ�Լ����ж��������λ��־�ж�
	PT0 = 0;		//��ʱ��0�ж����ȿ���λ��
}


/**
  * @brief ��ʱ��0�ж�ģ��
  *	@param	�� 
  *	@retval	��
  * @notes  ��Ϊģ�壬ʹ��ʱ����main.c��
 */
void Timer0_Routine() interrupt 1
{
	static unsigned int T0Count;
	TL0 = 0x66;		//���ö�ʱ��ֵ
	TH0 = 0xFC;		//���ö�ʱ��ֵ
	T0Count++;
	if(T0Count>=500)
	{
		T0Count=0;
		P2_0=~P2_0;
		g_time_flag=!g_time_flag;
	}
}