#include "TIME_COUNTING.H"

#define T2_reload_value		( 65536 - CLOCK_DIVISION )
#define	T2H_reload_value	( T2_reload_value / 0xFF )
#define T2L_reload_value	( T2_reload_value % 0xFF )

bit TIMER2_INTERRUPT_FLAG;

void T2_DIVIER( void ) interrupt 12
{
	T2L = T2H_reload_value;
	T2H = T2H_reload_value;										//try@kino 试一下会不会自动重载
	TIMER2_INTERRUPT_FLAG = SET_MARK;
	//IE2 &= ~0x04;	IE2 |= 0x04;								//try@kino 试一下要不要手动清除中断标志
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
    T2L = T2H_reload_value;
	T2H = T2H_reload_value;
	AUXR |= 0x1C;												//定时器2设为计数器，计数输入设为不分频，并允许T2开始运行
	IE2 |= 0x04;												//允许响应T2中断请求
	EA = SET_MARK;												//允许CPU响应中断
}

