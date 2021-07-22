#ifndef _IO_H_
#define _IO_H_

#include "stc8g.h"
#define  u8 unsigned char 
#define  u16 unsigned int
#define  u32 unsigned int

//PnM1.x / PnM0.x   ----   �˿�ģʽ���üĴ���
/************************
*   ׼˫���
*		�������
*		��������
*		��©���
**************************/

typedef enum{
	GPIO_PM_QD = 00,    
	GPIO_PM_PP = 01,
	GPIO_PM_HI = 10,
	GPIO_PM_OD = 11
}GPIOPM_TypeDef;

//�˿�����������ƼĴ���
typedef enum{
	GPIO_PU_EN = 1,
	GPIO_PU_DISEN = 0
}GPIOPU_TypeDef;

//�˿�ʩ���ش������ƼĴ���
typedef enum{
	GPIO_PNCS_EN = 0,
	GPIO_PNCS_DISEN = 1
}GPIOPNCS_TypeDef;

//�˿ڵ�ƽת���ٶȿ��ƼĴ���
typedef enum{
	GPIO_PSR_BIG = 0,
	GPIO_PSR_SMALL = 1
}GPIOPSR_TypeDef;

//�˿������������ƼĴ���
typedef enum{
	GPIO_PDR_BIG = 0,
	GPIO_PDR_SMALL = 1
}GPIOPDR_TypeDef;

//�˿������ź�����ʹ�ܿ��ƼĴ���
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
	GPIOPM_TypeDef   gpio_mode; 				//----   �˿�ģʽ���üĴ���
	GPIOPU_TypeDef   gpio_pxpu;					//----   �˿�����������ƼĴ���
	GPIOPNCS_TypeDef gpio_pxncs;				//----   �˿�ʩ���ش������ƼĴ���
	GPIOPSR_TypeDef  gpio_pxsr;					//----   �˿ڵ�ƽת���ٶȿ��ƼĴ���
	GPIOPDR_TypeDef  gpio_pxdr;					//----   �˿������������ƼĴ���
	GPIOPIE_TypeDef  gpio_pxie;					//----   �˿������ź�����ʹ�ܿ��ƼĴ���
}GPIO_InitTypeDef;

void IoBuild(GPIOX_TypeDef Gpio_gp, GPIOPINX_TypeDef Gpio_pin, GPIO_InitTypeDef Gpio_init);

#endif