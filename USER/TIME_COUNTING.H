#ifndef __TIME_COUNTING_H_
#define __TIME_COUNTING_H_

#include "INCLUDE.H"

#define EX_FOSC         32768
#define CLOCK_DIVISION	960

extern bit TIMER2_INTERRUPT_FLAG;

void TIME_COUNT_INIT( void );

#endif
