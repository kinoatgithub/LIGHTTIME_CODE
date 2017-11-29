#include "TIME_COUNTING.H"

#define T2_reload_value		( 0xFFFF - CLOCK_DIVISION )
#define	T2H_reload_value	( T2_reload_value / 0xFF )
#define T2L_reload_value	( T2_reload_value % 0xFF )

extern u16 GTR;
bit ONE_PULSE_TIMESUP_FLAG;
u16 ONE_PULSE_DELAY , ACCELERATION_DELAY , SWITCH_SCAN_DELAY;


void T0_DIVIER( void ) interrupt 1
{
	SWITCH_SCAN_DELAY++;
	ACCELERATION_DELAY++;
	if( ONE_PULSE_PERIOD < ONE_PULSE_DELAY )
	{
		ONE_PULSE_TIMESUP_FLAG = SET_MARK;
	}
	else
	{
		ONE_PULSE_DELAY++;
	}	
}

void TIME_COUNT_INIT(void)
{
	AUXR |= 0x80;				//定时器时钟1T模式
	TMOD &= 0xF2;				//设置T0为外部脉冲计数模式
	TL0 = T2L_reload_value;		//设置定时初值
	TH0 = T2H_reload_value;		//设置定时初值
	TF0 = 0;					//清除TF0标志
	TR0 = 1;					//定时器0开始计时
}

void SOFT_DELAY( u16 times )
{
	while( times-- )
	{
		GTR = SOFT_DELAY_UNIT; 
		while( GTR-- );
	}
}
