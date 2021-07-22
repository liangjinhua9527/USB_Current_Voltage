#ifndef _IO_H_
#define _IO_H_

#include "stc8g.h"
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int

//PnM1.x / PnM0.x   ----   端口模式配置寄存器
/************************
*   准双向口
*		推挽输出
*		高阻输入
*		开漏输出
**************************/

typedef enum{
	GPIO_PM_QD = 00,    
	GPIO_PM_PP = 01,
	GPIO_PM_HI = 10,
	GPIO_PM_OD = 11
}GPIOPM_TypeDef;

//端口上拉电阻控制寄存器
typedef enum{
	GPIO_PU_EN = 1,
	GPIO_PU_DISEN = 0
}GPIOPU_TypeDef;

//端口施密特触发控制寄存器
typedef enum{
	GPIO_PNCS_EN = 0,
	GPIO_PNCS_DISEN = 1
}GPIOPNCS_TypeDef;

//端口电平转换速度控制寄存器
typedef enum{
	GPIO_PSR_BIG = 0,
	GPIO_PSR_SMALL = 1
}GPIOPSR_TypeDef;

//端口驱动电流控制寄存器
typedef enum{
	GPIO_PDR_BIG = 0,
	GPIO_PDR_SMALL = 1
}GPIOPDR_TypeDef;

//端口数字信号输入使能控制寄存器
typedef enum{
	GPIO_PIE_EN = 1,
	GPIO_PIE_DISEN = 0
}GPIOPIE_TypeDef;

typedef enum{
	P_0 = 0,
	P_1 = 1,
	P_2 = 2,
	P_3 = 3,
	P_4 = 4,
	P_5 = 5
}GPIOX_TypeDef;

typedef enum{
	PIN0 = 0,
	PIN1 = 1,
	PIN2 = 2,
	PIN3 = 3,
	PIN4 = 4,
	PIN5 = 5,
	PIN6 = 6,
	PIN7 = 7
}GPIOPINX_TypeDef;

typedef struct
{
	GPIOPM_TypeDef   gpio_mode; 				//----   端口模式配置寄存器
	GPIOPU_TypeDef   gpio_pxpu;					//----   端口上拉电阻控制寄存器
	GPIOPNCS_TypeDef gpio_pxncs;				//----   端口施密特触发控制寄存器
	GPIOPSR_TypeDef  gpio_pxsr;					//----   端口电平转换速度控制寄存器
	GPIOPDR_TypeDef  gpio_pxdr;					//----   端口驱动电流控制寄存器
	GPIOPIE_TypeDef  gpio_pxie;					//----   端口数字信号输入使能控制寄存器
}GPIO_InitTypeDef;

void IoBuild(GPIOX_TypeDef Gpio_gp, GPIOPINX_TypeDef Gpio_pin, GPIO_InitTypeDef Gpio_init);

#endif