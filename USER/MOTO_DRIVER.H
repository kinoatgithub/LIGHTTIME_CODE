#ifndef __MOTO_DRIVER_H_
#define __MOTO_DRIVER_H_

#include "INCLUDE.H"

sbit 	PHASE_A	=	P5^4;
sbit 	PHASE_B	=	P5^5;
sbit 	PHASE_C	=	P3^3;
sbit	PHASE_D	=	P3^2;

void MOTO_DRIVER_INIT( void );
void MOTO_CONTROL( void );
void DEBUG_LED( void );

#endif																	//__MOTO_DRIVER_H_
