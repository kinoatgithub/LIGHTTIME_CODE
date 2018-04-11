#include "INCLUDE.H"
#include "MOTO_DRIVER.H"
#include "SWITCH.H"

void USER_SYS_INIT( void )
{
    MOTO_DRIVER_INIT();
}

void main( void )
{
    USER_SYS_INIT();
	while( 1 )
	{	
		extern u16 PC;
		extern bit dir;
		PC = 0;
		while( switch_pin == SET_MARK );
		dir = ~dir;
		while( PC != 2048 )
		{
			ONE_PULSE_DRIVING_CHECK();
		}
	}
}
		