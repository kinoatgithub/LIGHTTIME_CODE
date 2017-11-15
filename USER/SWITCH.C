#include "SWITCH.H"

sbit	switch_pin  =  P3^1;

void SWITCH_INIT( void )
{
	P3M0 |= 0x02 ;											//P3.1设置为开漏输出
	P3M1 |= 0x02 ;
}

DIRECTION_TYPE SCAN_SWITCH( void )
{
	u8 i ;
	bit befor_pull , after_pull;
	DIRECTION_TYPE now_direction;
	static u8 direction_hysteresis;
	static DIRECTION_TYPE last_direction , public_direction;
	befor_pull = switch_pin;
	switch_pin = RSE_MARK;
	i = SWITCH_DISCHARGE_PERIOD;
	while( i-- );
	switch_pin = SET_MARK;
	i = SWITCH_CHARGE_PERIOD;
	while( i-- );
	after_pull = switch_pin;
	if( after_pull != SET_MARK )
	{
		if( befor_pull != SET_MARK )																																									//检测到没串电容的按钮接通
		{
			now_direction = POS;
		}
		else
		{
			now_direction = NEG;																																										//检测到有串电容的按钮接通
		}
	}
	else
	{
		now_direction = NON;
	}
	if( last_direction != now_direction )
	{
		last_direction = now_direction;
		direction_hysteresis = 0;
	}
	else
	{
		direction_hysteresis++;
	}
	if( SWITCH_HYSTERESIS_VAL < direction_hysteresis )
	{
		direction_hysteresis = SWITCH_HYSTERESIS_VAL;
		public_direction = now_direction;
	}
	return public_direction;
}




