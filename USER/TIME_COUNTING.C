#include "TIME_COUNTING.H"



void TIMES_UP( void )	interrupt 12
{
	TIMER2_INTERRUPT_FLAG = SET_MARK;
}

RETURN_STATUS TIME_COUNT_INIT( void )
{
	u16 check_times = DELAY_FOR_UART_CONTACT;
    T2L = 0;
	CLOCK_COUNTER = 0;
	COUNT_OVERFLOWDE = RSE_MARK;
	while( check_times-- )
	{
		if( 4 <= CLOCK_COUNTER )													//在延时期间内抓捕到4个时钟周期
		{
			return SUCCESS;
		}
	}
	return ERROR;
}

