#ifndef _INA219_H_
#define _INA219_H_

#include "stc8g.h"	  	 
#include "io.h"
	
#define INA219_CMD  0	//Ð´ÃüÁî
#define INA219_DATA 1	//Ð´Êý¾Ý

sbit INA219_SCL=P3^2;//SCL
sbit INA219_SDA=P3^3;//SDA

void IIC_Start();
void IIC_Stop();
u8 IIC_Respond();
u8 IIC_MlaveRespond();
u8 IIC_SlaveRespond();
u8 IIC_Respond();
void INA219_GpioInit(void);
void INA219_SendByte(u16 iic_data,u8 slave_address,u8 slave_reg_address);
u16 INA219_ReceiveByte(u8 slave_address,u8 slave_reg_address);

#endif