#include "MOTO_DRIVER.H"
#include "TIME_COUNTING.H"
#include "SWITCH.H"

u8 moto_phase[2];

void MOTO_DRIVER_INIT( void )
{
//	P3M0 |= 0x0C;									//P3.2 & P3.3设置为推挽输出				//try@kino 复位后引脚为弱上拉模式，试一下可不可以驱动达林顿管。
//	P5M0 |= 0x03;									//P5.4 & P5.5设置为推挽输出
	moto_phase[ 0 ] = 0x11;
	TIME_COUNT_INIT();
    SWITCH_INIT();
}

void SET_PHASE( u8 phase )
{
	phase <<= 1;
	PHASE_A = CY;
	phase <<= 1;
	PHASE_B = CY;
	phase <<= 1;
	PHASE_C = CY;
	phase <<= 1;
	PHASE_D = CY;
}

float hard_delay( float delay_time )
{
	u8 i, j;
	float next_time;
	for( i = 0 ; 0 < ( delay_time - i ) ; i++ )
	{
		j = DELAY_UNIT;
		do
		{
			next_time *= ANGULAR_ACCELERATION_RATE;
		}
		while( j-- );
	}
	return next_time;
}

void MOTO_CONTROL( void )
{
	static bit step;
	static float next_times;
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
		SET_PHASE( 0 );
		if( TIMER2_INTERRUPT_FLAG == SET_MARK )
		{
			SET_PHASE( moto_phase[ 0 ] );
			moto_phase[ 0 ] = POS_ROTATE( moto_phase[ 0 ] );
			TIMER2_INTERRUPT_FLAG = RSE_MARK;
			hard_delay( ONE_PULSE_WIDTH );
			if( ( moto_phase[ 0 ] & 0x01 ) == SET_MARK )
			{
				moto_phase[ 0 ] = 0x11;
			}
		}
	}
}




