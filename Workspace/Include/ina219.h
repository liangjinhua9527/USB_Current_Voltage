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

/*******************************
* Current_LSB = MAX_Current / 2* 10 ^15
* Current_LSB = MAX_Current / 2* 10 ^12 //���üĴ������12Bit�ֱ���
	6.4A = 320mv / 0.05R  
	195uA = 6.4A / 2* 10 ^15            //I_LSB_MIN 
	1562uA = 6.4A / 2* 10 ^12						//I_LSB_MAX
	I_LSB��ѡֵ��ΧΪ I_LSB_MIN��I_LSB_MAX֮�䣬ѡ�񿿽�I_LSB_MIN
	ȡ����ֵ 200uA 
	I_LSB = 200 * 10 ^-6 = 0.0002A = 200uA 
	
*	Cal = 0.04096 /(Current_LSB * R)  //�Ĵ���05ֵ
	    = 0.04096 / 0.00001
			= 4096

*	Power_LSB = 20 * Current_LSB
						= 20 * 0.0002A
						= 0.004W
						= 4mw
*********************************/
#define INA219_Configuration_Register_Value  	 0x3c1f		// ��׼ֵ�Ĵ���ֵ  15391
#define INA219_Calibration_Register_Value  	   0x1000		// ��׼ֵ�Ĵ���ֵ  4096

#define Bus_Power_LSB    0.004		 		//���ʷֱ���4mw
#define Bus_Voltage_LSB  0.004		  //���ߵ�ѹ�ֱ���4mv
#define Bus_Current_LSB  0.0002		  //�����ֱ���0.2ma

	
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