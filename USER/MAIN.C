#include "INCLUDE.H"
#include "MOTO_DRIVER.H"
#include "SWITCH.H"

DIRECTION_TYPE LAST_DERECTION;

void main( void )
{
	while( 1 )
	{

	}
}
		
		
		
		
		
		
		
		
		DERECTION = GET_SWITCH_DIRECTION();
		if( PUBLIC_DERECTION != NON )
		{
			MOTO_LINEAR_ACCELERATER_MODE( PUBLIC_DERECTION );
		}
		else
		{
			if( TIMER2_INTERRUPT_FLAG == SET_MARK )
			{
				MOTO_ONE_PULSE_MODE( DRIVE_PULSE_WIDTH )
			}
		}
	}
}
