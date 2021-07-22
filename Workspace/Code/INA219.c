#include "INA219.H"
#include "oled.h"
#include "stdio.h"

void INA219_GpioInit(void)
{		
	GPIOX_TypeDef GPIOX;
	GPIOPINX_TypeDef GPIOPINX;
	GPIO_InitTypeDef GPIO_Init;

//	OLED_SDA,P33,开漏输出,数字信号输入使能,上拉关闭,施密特使能,转换速度一般,驱动电流控制弱
	GPIOX = P_3;
	GPIOPINX = PIN3;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   端口
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   端口上拉电阻控制寄存器
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   端口施密特触发控制寄存器
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   端口电平转换速度控制寄存器
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   端口驱动电流控制寄存器
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   端口数字信号输入使能控制寄存器	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);
	
//	OLED_SCL,P32,开漏输出,数字信号输入使能,上拉关闭,施密特使能,转换速度一般,驱动电流控制弱
	GPIOX = P_3;
	GPIOPINX = PIN2;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   推挽输出
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   端口上拉电阻控制寄存器
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   端口施密特触发控制寄存器
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   端口电平转换速度控制寄存器
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   端口驱动电流控制寄存器
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   端口数字信号输入使能控制寄存器	
	
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

//起始命令
void IIC_Start()
{
	I2CMSCR = 0x01; 
	Wait();
}

//停止命令
void IIC_Stop()
{
	I2CMSCR = 0x06; 
	Wait();
}

//接收从机应答信号,0应答,1非应答
u8 IIC_SlaveRespond()
{
	u8 receive_flag = 1;
	I2CMSCR = 0x03;
	Wait();
	receive_flag = (I2CMSST & 0x02) >> 1;
	return receive_flag;
}

//主机应答信号,0应答,1非应答
u8 IIC_MasterRespond()
{
	I2CMSST &= 0xfe;
	I2CMSCR = 0x05;
	Wait();
}

//主机发送数据
void IIC_MasterSendByte(u8 send_data)
{
	I2CTXD = send_data;
	I2CMSCR = 0x02;
	Wait();
}


//主机接受数据
u8 IIC_MasterReceiveByte()
{
	u8 receive_data = 0;
	
	I2CMSCR = 0x04;
	receive_data = I2CRXD;
	Wait();
	return receive_data;
}


//IIC发送byte
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	data_temp[0] = iic_data >> 8;
	data_temp[1] = (u8) iic_data;
	
	//判断总线是否处于忙

	iic_failure:
	P_SW2 = 0x80; 			//允许访问xfr寄存器
	I2CCFG = 0xe0;			//允许IIC功能,主机模式,速率176Khz
	I2CMSCR = 0x00; 	//不允许主机模式中断 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //判断是否处于空闲状态

	OLED_ShowChar(0,0,'1',8);//显示ASCII字符	
	
	//起始命令
	
	IIC_Start();
	
	//发送从机地址
	IIC_MasterSendByte(slave_address);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	//从机应答
	OLED_ShowChar(10,0,'2',8);//显示ASCII字符	

	//发送从机寄存器地址
	IIC_MasterSendByte(slave_reg_address );
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //从机应答
	
	OLED_ShowChar(20,0,'3',8);//显示ASCII字符	
	
	//发送数据
	IIC_MasterSendByte(0x90);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //从机应答
	OLED_ShowChar(30,0,'4',8);//显示ASCII字符	
	
	IIC_MasterSendByte(0x80);
	while(IIC_SlaveRespond() != 0)  goto iic_failure;  	  //从机应答
	OLED_ShowChar(40,0,'5',8);//显示ASCII字符	
	
	//停止命令
	IIC_Stop();
	P_SW2 = 0x00; 			//关闭访问xfr寄存器
	OLED_ShowChar(50,0,'6',8);//显示ASCII字符	
}

//IIC接收byte
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address)
{
	char buff[10] = {0};
	u8 data_temp[2] = {0};
	u16 receive_data = 0;
	int kk = 0;
	//判断总线是否处于忙

	iic_Recfailure:
	P_SW2 = 0x80; 			//允许访问xfr寄存器
	I2CCFG = 0xe0;			//允许IIC功能,主机模式,速率176Khz
	I2CMSCR = 0x00; 		//不允许主机模式中断 
	while((I2CMSST & 0x80) == 0x80)  goto iic_Recfailure; //判断是否处于空闲状态
		OLED_ShowChar(0,0,'7',8);//显示ASCII字符	
	
	//起始命令
	
	IIC_Start();
	
	//发送从机地址+写

	IIC_MasterSendByte(slave_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//从机应答
	OLED_ShowChar(0,0,'8',8);//显示ASCII字符	

	//发送从机寄存器地址

	IIC_MasterSendByte(slave_reg_address);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	  //从机应答
	OLED_ShowChar(0,0,'8',8);//显示ASCII字符	
	//起始命令
	IIC_Start();
	
	//发送从机地址+读
	IIC_MasterSendByte(slave_address |0x01);
	while(IIC_SlaveRespond() != 0)  goto iic_Recfailure;  	//从机应答


	//发送从机寄存器地址
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
	
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
//	
	kk = IIC_MasterReceiveByte();
	IIC_MasterRespond();
	
	//停止命令
	IIC_Stop();
	P_SW2 = 0x00; 			//关闭访问xfr寄存器
	
	receive_data = data_temp[1]; 
	sprintf(buff,"%d",kk);
	OLED_ShowString(0,2,buff,16);
	while(1);
	receive_data = ((u16)data_temp[0] << 8 | data_temp[1]);
	OLED_ShowChar(60,0,'7',8);//显示ASCII字符	
	return receive_data;
}
























