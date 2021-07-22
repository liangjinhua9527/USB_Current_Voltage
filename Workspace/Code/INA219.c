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
u8 IIC_MasterRespond()
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
	
	I2CMSCR = 0x04;
	receive_data = I2CRXD;
	Wait();
	return receive_data;
}


//IIC����byte
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	data_temp[0] = iic_data >> 8;
	data_temp[1] = (u8) iic_data;
	
	//�ж������Ƿ���æ

	iic_failure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 	//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //�ж��Ƿ��ڿ���״̬

	OLED_ShowChar(0,0,'1',8);//��ʾASCII�ַ�	
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ
	IIC_MasterSendByte(slave_address);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	//�ӻ�Ӧ��
	OLED_ShowChar(10,0,'2',8);//��ʾASCII�ַ�	

	//���ʹӻ��Ĵ�����ַ
	IIC_MasterSendByte(slave_reg_address );
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	OLED_ShowChar(20,0,'3',8);//��ʾASCII�ַ�	
	
	//��������
	IIC_MasterSendByte(0x90);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //�ӻ�Ӧ��
	OLED_ShowChar(30,0,'4',8);//��ʾASCII�ַ�	
	
	IIC_MasterSendByte(0x80);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //�ӻ�Ӧ��
	OLED_ShowChar(40,0,'5',8);//��ʾASCII�ַ�	
	
	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���
	OLED_ShowChar(50,0,'6',8);//��ʾASCII�ַ�	
}

//IIC����byte
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address)
{
	char buff[10] = {0};
	u8 data_temp[2] = {0};
	u16 receive_data = 0;
	int kk = 0;
	//�ж������Ƿ���æ

	iic_Recfailure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 		//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_Recfailure; //�ж��Ƿ��ڿ���״̬
		OLED_ShowChar(0,0,'7',8);//��ʾASCII�ַ�	
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ+д

	IIC_MasterSendByte(slave_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//�ӻ�Ӧ��
	OLED_ShowChar(0,0,'8',8);//��ʾASCII�ַ�	

	//���ʹӻ��Ĵ�����ַ

	IIC_MasterSendByte(slave_reg_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	  //�ӻ�Ӧ��
	OLED_ShowChar(0,0,'8',8);//��ʾASCII�ַ�	
	//��ʼ����
	IIC_Start();
	
	//���ʹӻ���ַ+��
	IIC_MasterSendByte(slave_address |0x01);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//�ӻ�Ӧ��


	//���ʹӻ��Ĵ�����ַ
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
	
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
//	
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
	
	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���
	
	receive_data = data_temp[1]; 
	sprintf(buff,"%d",kk);
	OLED_ShowString(0,2,buff,16);
	while(1);
	receive_data = ((u16)data_temp[0] << 8 | data_temp[1]);
	OLED_ShowChar(60,0,'7',8);//��ʾASCII�ַ�	
	return receive_data;
}
























