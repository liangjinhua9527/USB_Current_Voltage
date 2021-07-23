#ifndef _INA219_H_
#define _INA219_H_

#include "stc8g.h"	  	 
#include "io.h"

#define INA219_Write_Slave_Address  				 0x80  // 写
#define INA219_Read_Slave_Address  					 0x81		//读
	
#define INA219_Configuration_Register  0x00  // 模式配置寄存器 (R/W)
#define INA219_Shunt_voltage_Register  0x01		// 分流电阻电压寄存器 (R)
#define INA219_Bus_voltage_Register  	 0x02		 // 总线电压寄存器 (R)
#define INA219_Power_Register  				 0x03		 // 功率寄存器 (R)
#define INA219_Current_Register  			 0x04		// 电流寄存器 (R)
#define INA219_Calibration_Register  	 0x05		// 基准值寄存器 (R/W)	

/*******************************
* Current_LSB = MAX_Current / 2* 10 ^15
* Current_LSB = MAX_Current / 2* 10 ^12 //配置寄存器里的12Bit分辨率
	6.4A = 320mv / 0.05R  
	195uA = 6.4A / 2* 10 ^15            //I_LSB_MIN 
	1562uA = 6.4A / 2* 10 ^12						//I_LSB_MAX
	I_LSB的选值范围为 I_LSB_MIN和I_LSB_MAX之间，选择靠近I_LSB_MIN
	取整数值 200uA 
	I_LSB = 200 * 10 ^-6 = 0.0002A = 200uA 
	
*	Cal = 0.04096 /(Current_LSB * R)  //寄存器05值
	    = 0.04096 / 0.00001
			= 4096

*	Power_LSB = 20 * Current_LSB
						= 20 * 0.0002A
						= 0.004W
						= 4mw
*********************************/
#define INA219_Configuration_Register_Value  	 0x3c1f		// 基准值寄存器值  15391
#define INA219_Calibration_Register_Value  	   0x1000		// 基准值寄存器值  4096

#define Bus_Power_LSB    0.004		 		//功率分辨率4mw
#define Bus_Voltage_LSB  0.004		  //总线电压分辨率4mv
#define Bus_Current_LSB  0.0002		  //电流分辨率0.2ma

	
sbit INA219_SCL=P3^2;//SCL
sbit INA219_SDA=P3^3;//SDA

void Wait();
void IIC_Start();
void IIC_Stop();
void IIC_MlaveRespond();
void IIC_MasterNotRespond();
u8 IIC_SlaveRespond();
void INA219_GpioInit(void);
void IIC_MasterSendByte(u8 send_data);
u8 IIC_MasterReceiveByte();
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address);
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address);

#endif