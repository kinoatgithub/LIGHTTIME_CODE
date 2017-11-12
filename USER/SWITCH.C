#include "SWITCH.H"

#define switch_pin_num	1

sbit	switch_pin  =  P3^1;

RETURN_STATUS SWITCH_INIT( void )
{
	P3M0 |= 0x01 >> switch_pin_num;							//设置为开漏输出
	P3M1 |= 0x01 >> switch_pin_num;
}

SCAN_SWITCH( void )
{
    static cw,ccw;
	if( switch_pin != SET_MARK )
    {
        
    }
    else
    {
        switch_pin = RSE_MARK;
    }
}