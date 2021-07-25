#include "INA219.H"
#include "oled.h"
#include "stdio.h"

void INA219_GpioInit(void)
{		
	GPIOX_TypeDef GPIOX;
	GPIOPINX_TypeDef GPIOPINX;
	GPIO_InitTypeDef GPIO_Init;

//	OLED_SDA,P33,��©���,�����ź�����ʹ��,�����ر�,ʩ����ʹ��,ת���ٶ�һ��,��������������
	GPIOX = P_3;
	GPIOPINX = PIN3;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   �˿�
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   �˿�����������ƼĴ���
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   �˿�ʩ���ش������ƼĴ���
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   �˿ڵ�ƽת���ٶȿ��ƼĴ���
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   �˿������������ƼĴ���
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   �˿������ź�����ʹ�ܿ��ƼĴ���	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);
	
//	OLED_SCL,P32,��©���,�����ź�����ʹ��,�����ر�,ʩ����ʹ��,ת���ٶ�һ��,��������������
	GPIOX = P_3;
	GPIOPINX = PIN2;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   �������
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   �˿�����������ƼĴ���
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   �˿�ʩ���ش������ƼĴ���
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   �˿ڵ�ƽת���ٶȿ��ƼĴ���
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   �˿������������ƼĴ���
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   �˿������ź�����ʹ�ܿ��ƼĴ���	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);	
	
	INA219_SCL = 1;
	INA219_SDA = 1;
}

void Delay1ms()		//@24.000MHz
{
	unsigned char i, j;

	i = 24;
	j = 85;
	do
	{
		while (--j);
	} while (--i);
}

//ִ����ɼĴ��� I2CMSCR�� MSCMD ���������ж��ź�
void Wait()
{
	while (!(I2CMSST & 0x40));
	I2CMSST &= ~0x40;
}

//��ʼ����
void IIC_Start()
{
	I2CMSCR = 0x01; 
	Wait();
}

//ֹͣ����
void IIC_Stop()
{
	I2CMSCR = 0x06; 
	Wait();
}

//���մӻ�Ӧ���ź�,0Ӧ��,1��Ӧ��
u8 IIC_SlaveRespond()
{
	u8 receive_flag = 1;
	I2CMSCR = 0x03;
	Wait();
	receive_flag = (I2CMSST & 0x02) >> 1;
	return receive_flag;
}

//����Ӧ���ź�,0Ӧ��,1��Ӧ��
void IIC_MasterNotRespond()
{
	I2CMSST |= 0x01;
	I2CMSCR = 0x05;
	Wait();
}

//����Ӧ���ź�,0Ӧ��,1��Ӧ��
void IIC_MasterRespond()
{
	I2CMSST &= 0xfe;
	I2CMSCR = 0x05;
	Wait();
}

//������������
void IIC_MasterSendByte(u8 send_data)
{
	I2CTXD = send_data;
	I2CMSCR = 0x02;
	Wait();
}


//������������
u8 IIC_MasterReceiveByte()
{
	u8 receive_data = 0;
	//д������� I2C ���߿��������� SCL �ܽ��ϲ��� 8 ��ʱ�ӣ������� SDA �˿��϶�ȡ������
	//�������Ƶ� I2CRXD �Ĵ������Ƚ��ո�λ���ݣ�
	I2CMSCR = 0x04;
	Wait();
	receive_data = I2CRXD;
	return receive_data;
}


//IIC����byte
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	data_temp[0] = iic_data >> 8;
	data_temp[1] = iic_data & 0x00ff;
	
	//�ж������Ƿ���æ

	iic_Sendfailure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 	//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_Sendfailure; //�ж��Ƿ��ڿ���״̬
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ
	IIC_MasterSendByte(slave_address & 0xfe);
	while(IIC_SlaveRespond() != 0)  goto iic_Sendfailure;  	//�ӻ�Ӧ��


	//���ʹӻ��Ĵ�����ַ
	IIC_MasterSendByte(slave_reg_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Sendfailure;  	  //�ӻ�Ӧ��

	
	//��������
	IIC_MasterSendByte(data_temp[0]);
	while(IIC_SlaveRespond() != 0)  goto iic_Sendfailure;  	  //�ӻ�Ӧ��

	
	IIC_MasterSendByte(data_temp[1]);
	while(IIC_SlaveRespond() != 0)  goto iic_Sendfailure;  	  //�ӻ�Ӧ��

	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���

}

//IIC����byte
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address)
{

	int data_temp[2] = {0};
	u16 receive_data = 0;

	
	//�ж������Ƿ���æ

	iic_Recfailure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 		//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_Recfailure; //�ж��Ƿ��ڿ���״̬
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ+д

	IIC_MasterSendByte(slave_address & 0xfe);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//�ӻ�Ӧ��


	//���ʹӻ��Ĵ�����ַ

	IIC_MasterSendByte(slave_reg_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	  //�ӻ�Ӧ��

	//��ʼ����
	IIC_Start();
	
	//���ʹӻ���ַ+��
	IIC_MasterSendByte(slave_address |0x01);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//�ӻ�Ӧ��


	//���ʹӻ��Ĵ�����ַ

	data_temp[0] = IIC_MasterReceiveByte();
	IIC_MasterRespond();
	
	data_temp[1] = IIC_MasterReceiveByte();
	IIC_MasterNotRespond();
	
	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���
	receive_data = (data_temp[0] << 8 | data_temp[1]);
	return receive_data;
}
























