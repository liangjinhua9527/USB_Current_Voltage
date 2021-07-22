#include "stc8g.h"
#include "oled.h"
#include "stdio.h"
#include "INA219.H"

void main(void)
{
		char buff[10] = {0};
	int t = 122;
	OLED_Init();//初始化OLED 
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示	123
	while(1) 
	{		
		sprintf(buff,"6823%d",t);
		OLED_ShowString(0,0,buff,16);//显示ASCII字符	 
		OLED_ShowString(0,2,buff,16);//显示ASCII字符	 
//		delay_ms(500);
//		OLED_Clear();
	}	  

	
	
	
	
	
	
	
	
//	u8 t=' ';
//	OLED_Init();//初始化OLED 
//	OLED_ColorTurn(0);//0正常显示，1 反色显示
//  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示	
//	while(1) 
//	{		

//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowChinese(0,0,0,16);//中
//		OLED_ShowChinese(18,0,1,16);//景
//		OLED_ShowChinese(36,0,2,16);//园
//		OLED_ShowChinese(54,0,3,16);//电
//		OLED_ShowChinese(72,0,4,16);//子
//		OLED_ShowChinese(90,0,5,16);//科
//		OLED_ShowChinese(108,0,6,16);//技
//		OLED_ShowString(8,2,"ZHONGJINGYUAN",16);
//		delay_ms(500);
//		OLED_Clear();
//		OLED_ShowString(20,0,"2014/05/01",16);
//		OLED_ShowString(0,2,"ASCII:",16);  
//		OLED_ShowString(63,2,"CODE:",16);
//		OLED_ShowChar(48,2,t,16);//显示ASCII字符	   
//		t++;
//		if(t>'~')t=' ';
//		OLED_ShowNum(103,2,t,3,16);
//		delay_ms(500);
//		OLED_Clear();
//	}	  
//		return 0;
}