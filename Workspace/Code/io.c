#include "io.h"

void IoBuild(GPIOX_TypeDef Gpio_gp, GPIOPINX_TypeDef Gpio_pin, GPIO_InitTypeDef Gpio_init)
{
	switch(Gpio_gp){
	
		case P_0 :	
			
		//模式
		P0M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P0M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//上拉
		P0PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//施密特触发
		P0NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P0SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P0DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P0IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;

		case P_1 :
		//模式	
		P1M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P1M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//上拉
		P1PU = Gpio_init.gpio_pxpu  << Gpio_pin;
		
		//施密特触发
		P1NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P1SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P1DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P1IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_2 :
		//模式
		P2M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P2M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;

		//上拉
		P2PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//施密特触发
		P2NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P2SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P2DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P2IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_3 :
		//模式
		P3M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P3M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//上拉
		P3PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//施密特触发
		P3NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P3SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P3DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P3IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_4 :
		//模式
		P4M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P4M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//上拉
		P4PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//施密特触发
		P4NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P4SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P4DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P4IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_5 :
		//模式
		P5M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P5M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;	

		//上拉
		P5PU = Gpio_init.gpio_pxpu << Gpio_pin;	
		
		//施密特触发
		P5NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//电平转换速度
		P5SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//驱动电流
		P5DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//数字信号输入
		P5IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;	
	}
}