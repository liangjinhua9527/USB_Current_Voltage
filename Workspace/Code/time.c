#include "time.h"

 u16 second = 0;
 u16 minute = 0;
 u16 hour = 0;

void time_init()
{
	P_SW2 = 0x80;
	TMOD = 0x00; //模式 0
	TL0 = 0x30; //65536-24M/12/1000
	TH0 = 0xf8;
	TR0 = 1; //启动定时器
	ET0 = 1; //使能定时器中断
	EA = 1;
	P_SW2 = 0x00;
}

void TM0_Isr() interrupt 1
{
	static u16 i = 0;
	i++;
	if(i == 1000){
		second++;
		i = 0;
	}
	if(second == 60)
	{
		second = 0;
		minute ++;
		
		if(minute == 60)
		{
				minute = 0;
				hour ++;

				if(hour == 100) hour = 0;
		}
		
	}

}