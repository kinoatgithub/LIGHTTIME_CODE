#include "TIME_COUNTING.H"

#define T2_reload_value		( 65536 - CLOCK_DIVISION )
#define	T2H_reload_value	( T2_reload_value / 0xFF )
#define T2L_reload_value	( T2_reload_value % 0xFF )

void T2_DIVIER( void ) interrupt 12
{
	T2L = T2H_reload_value;
	T2H = T2H_reload_value;										//try@kino 试一下会不会自动重载
	TIMER2_INTERRUPT_FLAG = SET_MARK;
	//IE2 &= ~0x04;	IE2 |= 0x04;								//try@kino 试一下要不要手动清除中断标志
}

RETURN_STATUS TIME_COUNT_INIT( void )
{
	COUNT_OVERFLOWDE = RSE_MARK;
	TIMER2_INTERRUPT_FLAG = RSE_MARK;
	
	Timer0Init();
	
    T2L = T2H_reload_value;
	T2H = T2H_reload_value;
	AUXR |= 0x1C;												//定时器2设为计数器，计数输入设为不分频，并允许T2开始运行
	IE2 |= 0x04;												//允许响应T2中断请求
	EA = SET_MARK;												//允许CPU响应中断
	
	while( TIMER2_INTERRUPT_FLAG != SET_MARK );
	return SUCCESS;
}

void Timer0Init(void)		//70毫秒@11.0592MHz
{
	AUXR &= 0x7F;			//定时器时钟12T模式
	TMOD &= 0xF0;			//设置定时器模式
	TMOD |= 0x01;			//设置定时器模式
	TL0 = 0x00;				//设置定时初值
	TH0 = 0x00;				//设置定时初值
	TF0 = 0;				//清除TF0标志
	TR0 = 1;				//定时器0开始计时
}

