#include "INA219.H"

#define INA219_Configuration_Register  0x00  // ģʽ���üĴ��� (R/W)
#define INA219_Shunt_voltage_Register  0x01		// ���������ѹ�Ĵ��� (R)
#define INA219_Bus_voltage_Register  	 0x02		 // ���ߵ�ѹ�Ĵ��� (R)
#define INA219_Power_Register  				 0x03		 // ���ʼĴ��� (R)
#define INA219_Current_Register  			 0x04		// �����Ĵ��� (R)
#define INA219_Calibration_Register  	 0x05		// ��׼ֵ�Ĵ��� (R/W)

void INA219_GpioInit(void)
{		
	GPIOX_TypeDef GPIOX;
	GPIOPINX_TypeDef GPIOPINX;
	GPIO_InitTypeDef GPIO_Init;

//	OLED_SDA,P55,��©���,�����ź�����ʹ��,�����ر�,ʩ����ʹ��,ת���ٶ�һ��,��������������
	GPIOX = P_3;
	GPIOPINX = PIN2;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   �˿�
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   �˿�����������ƼĴ���
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   �˿�ʩ���ش������ƼĴ���
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   �˿ڵ�ƽת���ٶȿ��ƼĴ���
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   �˿������������ƼĴ���
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   �˿������ź�����ʹ�ܿ��ƼĴ���	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);
	
//	OLED_SCL,P54,��©���,�����ź�����ʹ��,�����ر�,ʩ����ʹ��,ת���ٶ�һ��,��������������
	GPIOX = P_3;
	GPIOPINX = PIN3;
	
	GPIO_Init.gpio_mode = GPIO_PM_PP;				//----   �������
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   �˿�����������ƼĴ���
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   �˿�ʩ���ش������ƼĴ���
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   �˿ڵ�ƽת���ٶȿ��ƼĴ���
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   �˿������������ƼĴ���
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   �˿������ź�����ʹ�ܿ��ƼĴ���	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);	
	
	INA219_SCL = 1;
	INA219_SDA = 1;
}

//��ʼ����
void IIC_Start()
{
	I2CMSCR = 0x01; 
}

//ֹͣ����
void IIC_Stop()
{
	I2CMSCR = 0x06; 
}

//���մӻ�Ӧ���ź�,0Ӧ��,1��Ӧ��
u8 IIC_Respond()
{
	u8 receive_data = 1;
	I2CMSCR = 0x03;
	receive_data = (I2CMSST & 0x02) >> 1;
	return receive_data;
}

//���մӻ�Ӧ���ź�,0Ӧ��,1��Ӧ��
u8 IIC_SlaveRespond()
{
	u8 receive_data = 1;
	I2CMSCR = 0x03;
	receive_data = (I2CMSST & 0x02) >> 1;
	return receive_data;
}

//����Ӧ���ź�,0Ӧ��,1��Ӧ��
u8 IIC_MasterRespond()
{
	I2CMSST &= 0xfe;
	I2CMSCR = 0x05;
}

//IIC����byte
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	data_temp[0] = (u8) (iic_data >> 8);
	data_temp[1] = (u8) iic_data;
	
	//�ж������Ƿ���æ

	iic_failure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 	//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //�ж��Ƿ��ڿ���״̬
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ

	I2CTXD = slave_address;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//�ӻ�Ӧ��

	//���ʹӻ��Ĵ�����ַ

	I2CTXD = slave_reg_address  & 0xfe;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	//��������

	I2CTXD = iic_data;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	I2CTXD = data_temp[0];
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	I2CTXD = data_temp[1];
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���
}

//IIC����byte
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	u16 receive_data = 0;
	//�ж������Ƿ���æ
	
	iic_failure:
	P_SW2 = 0x80; 			//�������xfr�Ĵ���
	I2CCFG = 0xe0;			//����IIC����,����ģʽ,����176Khz
	I2CMSCR = 0x00; 	//����������ģʽ�ж� 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //�ж��Ƿ��ڿ���״̬
	
	//��ʼ����
	
	IIC_Start();
	
	//���ʹӻ���ַ+д

	I2CTXD = slave_address & 0xfe; 
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//�ӻ�Ӧ��

	//���ʹӻ��Ĵ�����ַ

	I2CTXD = slave_reg_address;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //�ӻ�Ӧ��
	
	//��ʼ����
	IIC_Start();
	
	//���ʹӻ���ַ+��

	I2CTXD = slave_address | 0x01; 
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//�ӻ�Ӧ��

	//���ʹӻ��Ĵ�����ַ
	I2CMSCR = 0x04;
	data_temp[0] = I2CRXD;
	IIC_SlaveRespond();
	
	I2CMSCR = 0x04;
	data_temp[1] = I2CRXD;
	IIC_SlaveRespond();
	
	//ֹͣ����
	IIC_Stop();
	P_SW2 = 0x00; 			//�رշ���xfr�Ĵ���
	
	receive_data = ((u16)data_temp[0] << 8 | data_temp[1]);
	
	return receive_data;
}
























