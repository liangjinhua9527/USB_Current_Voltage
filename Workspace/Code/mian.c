#include "stc8g.h"
#include "oled.h"
#include <math.h>
#include "stdio.h"
#include "INA219.H"

void main(void)
{
	char buff[10] = {0};
	int ll=0;
	float value = 0.0f;
	int t = 0;
	OLED_Init();//初始化OLED 
	OLED_ColorTurn(0);//0正常显示，1 反色显示
  OLED_DisplayTurn(0);//0正常显示 1 屏幕翻转显示	123
	INA219_GpioInit();
	INA219_SendByte(INA219_Configuration_Register_Value,INA219_Write_Slave_Address,INA219_Configuration_Register); //模式配置寄存器
	INA219_SendByte(INA219_Calibration_Register_Value,INA219_Write_Slave_Address,INA219_Calibration_Register);		//基准值寄存器
	
	while(1) 
	{		
		
		ll = INA219_ReceiveByte(INA219_Read_Slave_Address, INA219_Bus_voltage_Register);
		value = (ll >> 3) * Bus_Voltage_LSB;
		
		sprintf(buff,"%.2fV",value);
		OLED_ShowString(0,2,buff,16);
		
		ll = 0,value = 0.0;
		INA219_SendByte(INA219_Configuration_Register_Value,INA219_Write_Slave_Address,INA219_Configuration_Register); //模式配置寄存器
		ll = INA219_ReceiveByte(INA219_Read_Slave_Address, INA219_Current_Register);
		value = ll  * Bus_Current_LSB;
		value = fabs(value);
		sprintf(buff,"%.2fA",value);

		OLED_ShowString(65,2,buff,16);
		
		ll = 0,value = 0.0;
		ll = INA219_ReceiveByte(INA219_Read_Slave_Address, INA219_Power_Register);
		value = ll  * Bus_Power_LSB;
		
		sprintf(buff,"%.2fW",value);
		OLED_ShowString(0,0,buff,16);
		
		ll = 0,value = 0.0;
		delay_ms(500);

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

}