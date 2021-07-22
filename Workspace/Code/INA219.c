#include "INA219.H"

#define INA219_Configuration_Register  0x00  // 模式配置寄存器 (R/W)
#define INA219_Shunt_voltage_Register  0x01		// 分流电阻电压寄存器 (R)
#define INA219_Bus_voltage_Register  	 0x02		 // 总线电压寄存器 (R)
#define INA219_Power_Register  				 0x03		 // 功率寄存器 (R)
#define INA219_Current_Register  			 0x04		// 电流寄存器 (R)
#define INA219_Calibration_Register  	 0x05		// 基准值寄存器 (R/W)

void INA219_GpioInit(void)
{		
	GPIOX_TypeDef GPIOX;
	GPIOPINX_TypeDef GPIOPINX;
	GPIO_InitTypeDef GPIO_Init;

//	OLED_SDA,P55,开漏输出,数字信号输入使能,上拉关闭,施密特使能,转换速度一般,驱动电流控制弱
	GPIOX = P_3;
	GPIOPINX = PIN2;
	
	GPIO_Init.gpio_mode = GPIO_PM_OD;				//----   端口
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   端口上拉电阻控制寄存器
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   端口施密特触发控制寄存器
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   端口电平转换速度控制寄存器
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   端口驱动电流控制寄存器
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   端口数字信号输入使能控制寄存器	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);
	
//	OLED_SCL,P54,开漏输出,数字信号输入使能,上拉关闭,施密特使能,转换速度一般,驱动电流控制弱
	GPIOX = P_3;
	GPIOPINX = PIN3;
	
	GPIO_Init.gpio_mode = GPIO_PM_PP;				//----   推挽输出
	GPIO_Init.gpio_pxpu = GPIO_PU_DISEN;		//----   端口上拉电阻控制寄存器
	GPIO_Init.gpio_pxncs = GPIO_PNCS_EN;	  //----   端口施密特触发控制寄存器
	GPIO_Init.gpio_pxsr = GPIO_PSR_SMALL;		//----   端口电平转换速度控制寄存器
	GPIO_Init.gpio_pxdr = GPIO_PDR_SMALL;		//----   端口驱动电流控制寄存器
	GPIO_Init.gpio_pxie = GPIO_PIE_EN;			//----   端口数字信号输入使能控制寄存器	
	
	IoBuild(GPIOX, GPIOPINX,GPIO_Init);	
	
	INA219_SCL = 1;
	INA219_SDA = 1;
}

//起始命令
void IIC_Start()
{
	I2CMSCR = 0x01; 
}

//停止命令
void IIC_Stop()
{
	I2CMSCR = 0x06; 
}

//接收从机应答信号,0应答,1非应答
u8 IIC_Respond()
{
	u8 receive_data = 1;
	I2CMSCR = 0x03;
	receive_data = (I2CMSST & 0x02) >> 1;
	return receive_data;
}

//接收从机应答信号,0应答,1非应答
u8 IIC_SlaveRespond()
{
	u8 receive_data = 1;
	I2CMSCR = 0x03;
	receive_data = (I2CMSST & 0x02) >> 1;
	return receive_data;
}

//主机应答信号,0应答,1非应答
u8 IIC_MasterRespond()
{
	I2CMSST &= 0xfe;
	I2CMSCR = 0x05;
}

//IIC发送byte
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	data_temp[0] = (u8) (iic_data >> 8);
	data_temp[1] = (u8) iic_data;
	
	//判断总线是否处于忙

	iic_failure:
	P_SW2 = 0x80; 			//允许访问xfr寄存器
	I2CCFG = 0xe0;			//允许IIC功能,主机模式,速率176Khz
	I2CMSCR = 0x00; 	//不允许主机模式中断 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //判断是否处于空闲状态
	
	//起始命令
	
	IIC_Start();
	
	//发送从机地址

	I2CTXD = slave_address;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//从机应答

	//发送从机寄存器地址

	I2CTXD = slave_reg_address  & 0xfe;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //从机应答
	
	//发送数据

	I2CTXD = iic_data;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //从机应答
	
	I2CTXD = data_temp[0];
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //从机应答
	
	I2CTXD = data_temp[1];
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //从机应答
	
	//停止命令
	IIC_Stop();
	P_SW2 = 0x00; 			//关闭访问xfr寄存器
}

//IIC接收byte
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address)
{
	u8 data_temp[2] = {0};
	u16 receive_data = 0;
	//判断总线是否处于忙
	
	iic_failure:
	P_SW2 = 0x80; 			//允许访问xfr寄存器
	I2CCFG = 0xe0;			//允许IIC功能,主机模式,速率176Khz
	I2CMSCR = 0x00; 	//不允许主机模式中断 
	while((I2CMSST & 0x80) == 0x80)  goto iic_failure; //判断是否处于空闲状态
	
	//起始命令
	
	IIC_Start();
	
	//发送从机地址+写

	I2CTXD = slave_address & 0xfe; 
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//从机应答

	//发送从机寄存器地址

	I2CTXD = slave_reg_address;
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	  //从机应答
	
	//起始命令
	IIC_Start();
	
	//发送从机地址+读

	I2CTXD = slave_address | 0x01; 
	I2CMSCR = 0x02;
	while(IIC_Respond() != 0x00)  goto iic_failure;  	//从机应答

	//发送从机寄存器地址
	I2CMSCR = 0x04;
	data_temp[0] = I2CRXD;
	IIC_SlaveRespond();
	
	I2CMSCR = 0x04;
	data_temp[1] = I2CRXD;
	IIC_SlaveRespond();
	
	//停止命令
	IIC_Stop();
	P_SW2 = 0x00; 			//关闭访问xfr寄存器
	
	receive_data = ((u16)data_temp[0] << 8 | data_temp[1]);
	
	return receive_data;
}
























