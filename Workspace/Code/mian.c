#include "stc8g.h"
#include "oled.h"
#include "stdio.h"
#include "INA219.H"

void main(void)
{
		char buff[10] = {0};
	int t = 122;
	OLED_Init();//��ʼ��OLED 
	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ	123
	while(1) 
	{		
		sprintf(buff,"6823%d",t);
		OLED_ShowString(0,0,buff,16);//��ʾASCII�ַ�	 
		OLED_ShowString(0,2,buff,16);//��ʾASCII�ַ�	 
//		delay_ms(500);
//		OLED_Clear();
	}	  

	
	
	
	
	
	
	
	
//	u8 t=' ';
//	OLED_Init();//��ʼ��OLED 
//	OLED_ColorTurn(0);//0������ʾ��1 ��ɫ��ʾ
//  OLED_DisplayTurn(0);//0������ʾ 1 ��Ļ��ת��ʾ	
//	while(1) 
//	{		

//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16);//��
//		OLED_ShowChinese(18,0,1,16);//��
//		OLED_ShowChinese(36,0,2,16);//԰
//		OLED_ShowChinese(54,0,3,16);//��
//		OLED_ShowChinese(72,0,4,16);//��
//		OLED_ShowChinese(90,0,5,16);//��
//		OLED_ShowChinese(108,0,6,16);//��
//		OLED_ShowString(8,2,"ZHONGJINGYUAN",16);
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowString(20,0,"2014/05/01",16);
//		OLED_ShowString(0,2,"ASCII:",16);  
//		OLED_ShowString(63,2,"CODE:",16);
//		OLED_ShowChar(48,2,t,16);//��ʾASCII�ַ�	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,2,t,3,16);
//		delay_ms(500);
//		OLED_Clear();
//	}	  
//		return 0;
}