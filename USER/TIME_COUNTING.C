#include "TIME_COUNTING.H"

#define T2_reload_value		( 0xFFFF - CLOCK_DIVISION )
#define	T2H_reload_value	( T2_reload_value / 0xFF )
#define T2L_reload_value	( T2_reload_value % 0xFF )

bit TIMER2_INTERRUPT_FLAG;

void T2_DIVIER( void ) interrupt 12
{//自动重载，不用清除中断标志
	TIMER2_INTERRUPT_FLAG = SET_MARK;
}

void Timer0Init(void)
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式为16位非自动重载
	TMOD |= 0x01;			//设置定时器模式为16位非自动重载
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

void TIME_COUNT_INIT( void )
{
	Timer0Init();
    T2L = 0x00;
	T2H = 0x1F;
	AUXR |= 0x18;												//定时器2设为计数器，计数输入设为不分频，并允许T2开始运行
	AUXR |= 0x04;												//1分频
	IE2 |= 0x04;												//允许响应T2中断请求
	EA = SET_MARK;												//允许CPU响应中断
}

