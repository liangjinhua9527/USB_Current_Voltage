#ifndef _INA219_H_
#define _INA219_H_

#include "stc8g.h"	  	 
#include "io.h"

#define INA219_Write_Slave_Address  				 0x80  // д
#define INA219_Read_Slave_Address  					 0x81		//��
	
#define INA219_Configuration_Register  0x00  // ģʽ���üĴ��� (R/W)
#define INA219_Shunt_voltage_Register  0x01		// ���������ѹ�Ĵ��� (R)
#define INA219_Bus_voltage_Register  	 0x02		 // ���ߵ�ѹ�Ĵ��� (R)
#define INA219_Power_Register  				 0x03		 // ���ʼĴ��� (R)
#define INA219_Current_Register  			 0x04		// �����Ĵ��� (R)
#define INA219_Calibration_Register  	 0x05		// ��׼ֵ�Ĵ��� (R/W)	
	
sbit INA219_SCL=P3^2;//SCL
sbit INA219_SDA=P3^3;//SDA

void Wait();
void IIC_Start();
void IIC_Stop();
u8 IIC_Respond();
u8 IIC_MlaveRespond();
u8 IIC_SlaveRespond();
void INA219_GpioInit(void);
void IIC_MasterSendByte(u8 send_data);
u8 IIC_MasterReceiveByte();
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address);
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address);

#endif