#include "MOTO_DRIVER.H"
#include "TIME_COUNTING.H"
#include "SWITCH.H"

u8 moto_phase[2];

static u8 bug_reg;

void DEBUG_LED( void )
{
	PHASE_D = ~PHASE_D;
}

u8 POS_ROTATE( u8 x )
{
	return ((( x ) >> 1 ) | (( x ) << 3 ));
}

u8 NEG_ROTATE( u8 x )
{
	return ((( x ) << 1 ) | (( x ) >> 3 ));
}

void SET_PHASE( u8 phase )
{
	PHASE_A = phase & 0x08;
	PHASE_B = phase & 0x04;
	PHASE_C	= phase & 0x02;
	PHASE_D = phase & 0x01;
}

void MOTO_DRIVER_INIT( void )
{
	moto_phase[ 0 ] = 0x11;
	TIME_COUNT_INIT();
	SWITCH_INIT();
	P3M0 |= 0x0C;									//P3.2 & P3.3必须设置为推挽输出
	P5M0 |= 0x30;									//P5.4 & P5.5必须设置为推挽输出
	SET_PHASE( 0 );
}

u16 hard_delay( u16 delay_time )
{
	u16 i, j;
	u16 next_time;
//	static u16 time_tail;
	for( i = 0 ; 0 < ( delay_time - i ) ; i++ )
	{
		j = DELAY_UNIT;
		do
		{
//			next_time = (( delay_time * ANGULAR_ACCELERATION_RATE ) / ANTI_JAGGIES );
//			time_tail = (( delay_time * ANGULAR_ACCELERATION_RATE + time_tail ) % ANTI_JAGGIES );
//			if( next_time < MIN_DELAY_TIME )
//				next_time = MIN_DELAY_TIME;
			
//			next_time = (( delay_time * ANGULAR_ACCELERATION_RATE + time_tail ) / ANTI_JAGGIES );
//			time_tail = (( delay_time * ANGULAR_ACCELERATION_RATE + time_tail ) % ANTI_JAGGIES );
//			if( next_time < MIN_DELAY_TIME )
//				next_time = MIN_DELAY_TIME;
		}
		while( j-- );
	}
	return next_time;
}

void MOTO_CONTROL( void )
{
	static bit step;
	static u16 next_times = 600;
	DIRECTION_TYPE now_direction;
	static DIRECTION_TYPE last_direction;
	if( TF0 != RSE_MARK )
	{
		now_direction = SCAN_SWITCH();
		if( last_direction != now_direction )
		{
			moto_phase[ 1 ] = moto_phase[ 0 ];
			next_times = DELAY_INITIAL_VALUE;
			last_direction = now_direction;
		}
		TL0 = 0x00;				//设置定时初值
		TH0 = 0x00;				//设置定时初值
		TF0 = RSE_MARK;			//清除TF0标志
																		DEBUG_LED();
	}
	if( last_direction != NON )
	{
		if( last_direction == POS )
			moto_phase[ step ] = POS_ROTATE( moto_phase[ step ] );
		else
			moto_phase[ step ] = NEG_ROTATE( moto_phase[ step ] );
		step = ~step;
		SET_PHASE( moto_phase[ 0 ] | moto_phase[ 1 ] );
		next_times = hard_delay( next_times );
	}
	else

	{
		if( TIMER2_INTERRUPT_FLAG == SET_MARK )
		{
			SET_PHASE( moto_phase[ 0 ] );
			moto_phase[ 0 ] = POS_ROTATE( moto_phase[ 0 ] );
			TIMER2_INTERRUPT_FLAG = RSE_MARK;
			hard_delay( ONE_PULSE_WIDTH );
			SET_PHASE( 0 );
			if( ( moto_phase[ 0 ] & 0x10 ) == SET_MARK )
			{
				moto_phase[ 0 ] = 0x11;
			}
		}
	}	
}




