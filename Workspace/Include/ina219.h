#ifndef _INA219_H_
#define _INA219_H_

#include "stc8g.h"	  	 
#include "io.h"
	
#define INA219_CMD  0	//д����
#define INA219_DATA 1	//д����

sbit INA219_SCL=P3^2;//SCL
sbit INA219_SDA=P3^3;//SDA


void INA219_GpioInit(void);

#endif