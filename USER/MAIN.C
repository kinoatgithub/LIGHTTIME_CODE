#include "INCLUDE.H"
#include "MOTO_DRIVER.H"
#include "SWITCH.H"

DIRECTION_TYPE LAST_DERECTION;
void USER_SYS_INIT( void )
{
    MOTO_DRIVER_INIT();
    
}

void main( void )
{
    USER_SYS_INIT();
	while( 1 )
	{
        MOTO_CONTROL();
	}
}
		