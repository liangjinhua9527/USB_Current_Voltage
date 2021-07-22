#include "io.h"

void IoBuild(GPIOX_TypeDef Gpio_gp, GPIOPINX_TypeDef Gpio_pin, GPIO_InitTypeDef Gpio_init)
{
	switch(Gpio_gp){
	
		case P_0 :	
			
		//ģʽ
		P0M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P0M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//����
		P0PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//ʩ���ش���
		P0NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P0SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P0DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P0IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;

		case P_1 :
		//ģʽ	
		P1M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P1M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//����
		P1PU = Gpio_init.gpio_pxpu  << Gpio_pin;
		
		//ʩ���ش���
		P1NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P1SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P1DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P1IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_2 :
		//ģʽ
		P2M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P2M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;

		//����
		P2PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//ʩ���ش���
		P2NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P2SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P2DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P2IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_3 :
		//ģʽ
		P3M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P3M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//����
		P3PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//ʩ���ش���
		P3NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P3SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P3DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P3IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_4 :
		//ģʽ
		P4M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P4M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;
		
		//����
		P4PU = Gpio_init.gpio_pxpu << Gpio_pin;
		
		//ʩ���ش���
		P4NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P4SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P4DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P4IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;
	
		case P_5 :
		//ģʽ
		P5M0 = (Gpio_init.gpio_mode & 0x01) << Gpio_pin;
		P5M1 = ((Gpio_init.gpio_mode & 0x02) >> 1) << Gpio_pin;	

		//����
		P5PU = Gpio_init.gpio_pxpu << Gpio_pin;	
		
		//ʩ���ش���
		P5NCS = Gpio_init.gpio_pxncs  << Gpio_pin;
		
		//��ƽת���ٶ�
		P5SR = Gpio_init.gpio_pxsr << Gpio_pin;
		
		//��������
		P5DR = Gpio_init.gpio_pxdr  << Gpio_pin;		

		//�����ź�����
		P5IE = Gpio_init.gpio_pxie  << Gpio_pin;	
		break;	
	}
}