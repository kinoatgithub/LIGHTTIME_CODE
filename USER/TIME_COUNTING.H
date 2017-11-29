#ifndef __TIME_COUNTING_H_
#define __TIME_COUNTING_H_

#include "INCLUDE.H"

#define EX_FOSC         32768
#define CLOCK_DIVISION	960

void TIME_COUNT_INIT( void );
void SOFT_DELAY( u16 times );

#endif
